// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-18
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/FunctionDecl.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "用法: Infine.exe <源文件.ic>\n";
        std::cerr << "Usage: Infine.exe <source.ic>\n";
        std::cin.get();
        return 1;
    }

    std::string sourcePath = argv[1];
    std::ifstream inFile(sourcePath);
    if (!inFile.is_open()) {
        std::cerr << "错误: 无法打开文件 " << sourcePath << "\n";
        std::cerr << "Error: Cannot open file " << sourcePath << "\n";
        std::cin.get();
        return 1;
    }
    std::string code((std::istreambuf_iterator<char>(inFile)),
        std::istreambuf_iterator<char>());
    inFile.close();

    // 1. 词法分析
    infine::Lexer lexer(code);
    auto tokens = lexer.tokenize();

    // 2. 语法分析
    infine::Parser parser(tokens);
    auto ast = parser.parseProgram();

    // 3. 初始化 LLVM
    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module = LLVMModuleCreateWithNameInContext("Infine", context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    // 4. 生成 IR
    LLVMValueRef func = ast->codegen(module, builder);
    if (!func) {
        std::cerr << "IR 生成失败\n";
        std::cerr << "IR generation failed\n";
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        std::cin.get();
        return 1;
    }

    // 5. 输出 IR 到文件
    char* irString = LLVMPrintModuleToString(module);
    std::ofstream irFile("output.ll");
    if (!irFile.is_open()) {
        std::cerr << "无法写入 IR 文件\n";
        LLVMDisposeMessage(irString);
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        std::cin.get();
        return 1;
    }
    irFile << irString;
    irFile.close();
    LLVMDisposeMessage(irString);

    // 6. 使用 llc 将 IR 编译为 .obj（依赖 PATH 中的 llc）
    std::string objCmd = "llc -filetype=obj output.ll -o output.obj";
    std::cout << "执行编译命令: " << objCmd << "\n";
    int objResult = system(objCmd.c_str());
    if (objResult != 0) {
        std::cerr << "编译到目标文件失败，返回码: " << objResult << "\n";
        std::cerr << "请确保 llc 在 PATH 中\n";
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        std::cin.get();
        return 1;
    }

    // 7. 使用 lld-link 生成 .exe（依赖 PATH 中的 lld-link）
    std::string linkCmd = "lld-link output.obj /out:a.exe /subsystem:console /entry:main /nodefaultlib /defaultlib:libcmt /defaultlib:oldnames";
    std::cout << "执行链接命令: " << linkCmd << "\n";
    int lldResult = system(linkCmd.c_str());

    if (lldResult != 0) {
        std::cerr << "链接失败，返回码: " << lldResult << "\n";
        std::cerr << "请确保 lld-link 在 PATH 中\n";
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
        remove("output.obj");
        std::cin.get();
        return 1;
    }

    // 8. 清理临时文件
    remove("output.ll");
    remove("output.obj");

    // 9. 释放 LLVM 资源
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    std::cout << "编译成功，生成 a.exe\n";
    std::cout << "Build succeeded, generated a.exe\n";

    // 防止控制台闪退（成功时也等待输入）
    std::cin.get();
    return 0;
}