// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-09-25
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <memory>
#include <stdexcept>
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/FunctionDecl.h"

namespace fs = std::filesystem;

// ============================================================================
// 打印帮助信息
// ============================================================================
void printHelp() {
    std::cout << "Infine 0.0.7\n"
        << "Usage: Infine <command> [filename]\n\n"
        << "Commands:\n"
        << "  build <filename.ic>    Compile the specified Infine source file\n"
        << "  run   <filename.ic>    Compile and run the specified Infine source file\n"
        << "  --help                 Show this help message\n"
        << "  --version              Show version information\n"
        << "  cli                    Enter interactive CLI mode (default if no args)\n";
}

// ============================================================================
// 打印版本信息
// ============================================================================
void printVersion() {
    std::cout << "Infine 0.0.7\n";
}

// ============================================================================
// 从文件读取源码
// ============================================================================
std::string readSourceFile(const std::string& path, bool& ok) {
    std::ifstream file(path);
    if (!file.is_open()) {
        ok = false;
        return "";
    }
    std::string code((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();
    ok = true;
    return code;
}

// ============================================================================
// 执行子进程（用于 run 模式）
// ============================================================================
int runExecutable(const std::string& exePath) {
    std::string cmd = "\"" + exePath + "\"";
    return std::system(cmd.c_str());
}

// ============================================================================
// 编译核心函数（从源码字符串到生成 a.exe）
// 返回值：true 表示成功，false 表示失败
// ============================================================================
bool compileSource(const std::string& code, bool runAfterBuild = false) {
    // ---- 词法分析与语法分析（可能抛异常）----
    std::unique_ptr<infine::ASTNode> ast;
    try {
        infine::Lexer lexer(code);
        auto tokens = lexer.tokenize();

        infine::Parser parser(tokens);
        ast = parser.parseProgram();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return false;
    }

    // ---- 初始化 LLVM ----
    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module = LLVMModuleCreateWithNameInContext("Infine", context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    // ---- 生成 IR（多函数共享同一 Module）----
    LLVMValueRef func = ast->codegen(module, builder);
    if (!func) {
        std::cerr << "Error: IR generation failed\n";
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        return false;
    }

    // ---- 输出 IR 到文件 ----
    char* irString = LLVMPrintModuleToString(module);
    std::ofstream irFile("output.ll");
    if (!irFile.is_open()) {
        std::cerr << "Error: cannot write IR file\n";
        LLVMDisposeMessage(irString);
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        return false;
    }
    irFile << irString;
    irFile.close();
    LLVMDisposeMessage(irString);

    // ---- 调用 llc 编译 IR 为 .obj ----
    std::string objCmd = "llc -filetype=obj output.ll -o output.obj";
    int objResult = std::system(objCmd.c_str());
    if (objResult != 0) {
        std::cerr << "Error: llc failed (return code: " << objResult << ")\n";
        std::cerr << "       Please ensure llc is in your PATH.\n";
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        return false;
    }

    // ---- 调用 lld-link 生成 .exe ----
    std::string linkCmd = "lld-link output.obj /out:a.exe /subsystem:console /entry:main /nodefaultlib /defaultlib:libcmt /defaultlib:oldnames";
    int lldResult = std::system(linkCmd.c_str());
    if (lldResult != 0) {
        std::cerr << "Error: lld-link failed (return code: " << lldResult << ")\n";
        std::cerr << "       Please ensure lld-link is in your PATH.\n";
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        remove("output.obj");
        return false;
    }

    // ---- 清理临时文件 ----
    remove("output.ll");
    remove("output.obj");

    // ---- 释放 LLVM 资源 ----
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    std::cout << "Build succeeded, generated a.exe\n";

    // ---- 如果是 run 模式，执行 a.exe ----
    if (runAfterBuild) {
        int runResult = runExecutable("a.exe");
        if (runResult != 0) {
            std::cerr << "Error: running a.exe failed (exit code: " << runResult << ")\n";
            return false;
        }
    }

    return true;
}

// ============================================================================
// 编译文件函数
// ============================================================================
bool buildFile(const std::string& sourcePath, bool runAfterBuild = false) {
    if (!fs::exists(sourcePath)) {
        std::cerr << "Error: file not found: " << sourcePath << "\n";
        return false;
    }

    bool readOk;
    std::string code = readSourceFile(sourcePath, readOk);
    if (!readOk) {
        std::cerr << "Error: cannot read file: " << sourcePath << "\n";
        return false;
    }

    return compileSource(code, runAfterBuild);
}

// ============================================================================
// CLI 交互式模式
// ============================================================================
void runCliMode() {
    const std::string PROMPT = "Infine> ";
    std::string line;
    std::vector<std::string> history;

    std::cout << "Infine 0.0.7 - Interactive CLI\n";
    std::cout << "Type 'help' for commands, 'exit' to quit.\n\n";

    while (true) {
        std::cout << PROMPT;
        std::getline(std::cin, line);

        // 去除首尾空格
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            continue;
        }
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        // 空行跳过
        if (line.empty()) continue;

        // 记录历史
        history.push_back(line);

        // ---- 命令解析 ----
        if (line == "exit" || line == "quit") {
            std::cout << "Goodbye!\n";
            break;
        }
        else if (line == "help") {
            std::cout << "Commands:\n"
                << "  build <filename.ic>    Compile the specified file\n"
                << "  run <filename.ic>      Compile and run the specified file\n"
                << "  exit / quit            Exit CLI\n"
                << "  help                   Show this help\n"
                << "  clear                  Clear screen\n"
                << "  version                Show version\n"
                << "  history                Show command history\n";
        }
        else if (line == "clear") {
            std::cout << "\033[2J\033[1;1H";
        }
        else if (line == "version") {
            printVersion();
        }
        else if (line == "history") {
            for (size_t i = 0; i < history.size(); ++i) {
                std::cout << "  " << (i + 1) << "  " << history[i] << "\n";
            }
        }
        else if (line.rfind("build ", 0) == 0) {
            std::string filename = line.substr(6);
            size_t s = filename.find_first_not_of(" \t");
            if (s != std::string::npos) {
                filename = filename.substr(s);
            }
            if (filename.empty()) {
                std::cerr << "Error: missing filename. Usage: build <filename.ic>\n";
                continue;
            }
            bool ok = buildFile(filename, false);
            if (!ok) {
                std::cerr << "Build failed.\n";
            }
        }
        else if (line.rfind("run ", 0) == 0) {
            std::string filename = line.substr(4);
            size_t s = filename.find_first_not_of(" \t");
            if (s != std::string::npos) {
                filename = filename.substr(s);
            }
            if (filename.empty()) {
                std::cerr << "Error: missing filename. Usage: run <filename.ic>\n";
                continue;
            }
            bool ok = buildFile(filename, true);
            if (!ok) {
                std::cerr << "Run failed.\n";
            }
        }
        else {
            // 尝试作为文件名直接编译
            if (fs::exists(line)) {
                bool ok = buildFile(line, false);
                if (!ok) {
                    std::cerr << "Build failed.\n";
                }
            }
            else {
                std::cerr << "Unknown command: " << line << ". Type 'help' for commands.\n";
            }
        }
    }
}

// ============================================================================
// 主函数入口
// ============================================================================
int main(int argc, char* argv[]) {
    // ---- 无参数：进入交互式 CLI ----
    if (argc == 1) {
        runCliMode();
        return 0;
    }

    std::string command = argv[1];

    // ---- 处理帮助和版本 ----
    if (command == "--help" || command == "-h") {
        printHelp();
        return 0;
    }
    else if (command == "--version" || command == "-v") {
        printVersion();
        return 0;
    }

    // ---- 处理 cli 命令 ----
    if (command == "cli") {
        runCliMode();
        return 0;
    }

    // ---- 处理 build 和 run 命令 ----
    if (command == "build" || command == "run") {
        if (argc < 3) {
            std::cerr << "Error: missing filename. Use --help for usage.\n";
            return 1;
        }
        std::string sourcePath = argv[2];
        bool runAfter = (command == "run");
        bool ok = buildFile(sourcePath, runAfter);
        return ok ? 0 : 1;
    }

    // ---- 未知命令 ----
    std::cerr << "Error: unknown command '" << command << "'. Use --help for usage.\n";
    return 1;
}