// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/FunctionDecl.h"

// 编译器主入口：词法分析 → 语法分析 → IR 生成 → 输出文件
// Compiler entry point: lexing → parsing → IR generation → file output
int main() {
    std::cout << "Infine Code Compiler 0.0.4\n\n";

    // 测试源码（硬编码，后续将改为文件输入）
    // Test source code (hardcoded, will be replaced by file input later)
    std::string code = R"(
        func int main() {
            return 0;
        }
    )";

    // 1. 词法分析
    // 1. Lexical analysis
    infine::Lexer lexer(code);
    auto tokens = lexer.tokenize();

    // 输出 Token 列表（调试用）
    // Output token list (for debugging)
    for (const auto& tok : tokens) {
        std::cout << "[" << tok.typeName() << "] \""
            << tok.lexeme << "\" at " << tok.line << ":" << tok.column << "\n";
    }

    // 2. 语法分析
    // 2. Syntax analysis
    infine::Parser parser(tokens);
    auto ast = parser.parseProgram();  // 返回 AST 根节点（FunctionDecl）

    std::cout << "\nAST: " << ast->print() << "\n";

    // 3. 初始化 LLVM 环境
    // 3. Initialize LLVM environment
    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module = LLVMModuleCreateWithNameInContext("Infine", context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    // 4. 生成 IR
    // 4. Generate IR
    LLVMValueRef func = ast->codegen(module, builder);
    if (!func) {
        std::cerr << "Code generation failed.\n";
        return 1;
    }

    // 5. 输出 IR 到文件
    // 5. Write IR to file
    char* irString = LLVMPrintModuleToString(module);
    std::ofstream file("output.ll");
    if (file.is_open()) {
        file << irString;
        file.close();
        std::cout << "\nIR written to output.ll\n";
    }
    else {
        std::cerr << "Failed to open output.ll for writing.\n";
    }
    LLVMDisposeMessage(irString);

    // 6. 释放资源
    // 6. Free resources
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    std::cin.get();
    return 0;
}