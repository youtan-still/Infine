// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#include "FunctionDecl.h"
#include <llvm-c/Core.h>
#include <stdexcept>

namespace infine {

    FunctionDecl::FunctionDecl(std::string n, std::string rt,
        std::unique_ptr<BlockStmt> b)
        : name(std::move(n)), returnType(std::move(rt)), body(std::move(b)) {
    }

    std::string FunctionDecl::print() const {
        return "FunctionDecl(" + name + ", " + returnType + ", " +
            (body ? body->print() : "null") + ")";
    }

    // 生成函数定义的 IR：创建函数类型，添加函数，生成函数体
    // Generates IR for function definition: creates function type, adds function, emits body
    LLVMValueRef FunctionDecl::codegen(LLVMModuleRef module, LLVMBuilderRef builder) {
        LLVMContextRef context = LLVMGetModuleContext(module);

        // 目前仅支持 int 返回类型，后续可扩展
        // Currently only int return type is supported, can be extended later
        LLVMTypeRef returnTypeLLVM = LLVMInt32TypeInContext(context);

        // 函数类型：int func(void)
        // Function type: int func(void)
        LLVMTypeRef funcType = LLVMFunctionType(returnTypeLLVM, nullptr, 0, 0);

        // 在模块中添加函数声明
        // Add function declaration to the module
        LLVMValueRef function = LLVMAddFunction(module, name.c_str(), funcType);

        // 创建入口基本块并定位生成位置
        // Create entry basic block and position the builder
        LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, function, "entry");
        LLVMPositionBuilderAtEnd(builder, entry);

        // 生成函数体
        // Generate function body
        if (body) {
            body->codegen(module, builder);
        }
        else {
            // 空函数体默认返回 0
            // Empty body defaults to returning 0
            LLVMValueRef zero = LLVMConstInt(returnTypeLLVM, 0, 0);
            LLVMBuildRet(builder, zero);
        }

        return function;
    }

} // namespace infine