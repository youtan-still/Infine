// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#include "ReturnStmt.h"
#include <llvm-c/Core.h>

namespace infine {

    ReturnStmt::ReturnStmt(std::unique_ptr<ASTNode> e) : expr(std::move(e)) {}

    std::string ReturnStmt::print() const {
        return "ReturnStmt(" + (expr ? expr->print() : "null") + ")";
    }

    // 生成返回指令，如果有表达式则先计算表达式值
    // Generates a return instruction, evaluating the expression if present
    LLVMValueRef ReturnStmt::codegen(LLVMModuleRef module, LLVMBuilderRef builder) {
        LLVMValueRef retVal = expr ? expr->codegen(module, builder) : nullptr;
        return LLVMBuildRet(builder, retVal);
    }

} // namespace infine