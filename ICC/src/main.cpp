// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.3
// 日期：2026-08-03
// 路径：ICC/src/main.cpp
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>
#include "lexer/Lexer.h"

int main() {
    std::cout << "Infine Code Compiler 0.0.3\n\n";

    std::string code = R"(
        func int main() {
            return 0;
        }
    )";

    // 1. 词法分析（仅演示，不参与 IR 生成）
    infine::Lexer lexer(code);
    auto tokens = lexer.tokenize();

    for (const auto& tok : tokens) {
        std::cout << "[" << tok.typeName() << "] \""
            << tok.lexeme << "\" at " << tok.line << ":" << tok.column << "\n";
    }

    // 2. 使用 LLVM C API 生成 IR
    std::cout << "\nGenerating LLVM IR...\n";

    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module = LLVMModuleCreateWithNameInContext("Infine", context);

    // 创建函数类型：int main()
    LLVMTypeRef returnType = LLVMInt32TypeInContext(context);
    LLVMTypeRef funcType = LLVMFunctionType(returnType, nullptr, 0, 0);
    LLVMValueRef func = LLVMAddFunction(module, "main", funcType);

    // 创建基本块并设置插入点
    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, func, "entry");
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, entry);

    // 生成 return 0
    LLVMValueRef zero = LLVMConstInt(returnType, 0, 0);
    LLVMBuildRet(builder, zero);

    // 输出 IR
    char* irString = LLVMPrintModuleToString(module);
    std::ofstream file("output.ll");
    if (file.is_open()) {
        file << irString;
        file.close();
        std::cout << "IR written to output.ll\n";
    }
    else {
        std::cerr << "Failed to open output.ll for writing.\n";
    }
    LLVMDisposeMessage(irString);

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    std::cin.get();
    return 0;
}