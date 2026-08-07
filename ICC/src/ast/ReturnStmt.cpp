// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.3
// 日期：2026-08-02
// 路径：ICC/src/ast/ReturnStmt.cpp
// -----------------------------------------------------------------------------

#include "ReturnStmt.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

namespace infine {

    ReturnStmt::ReturnStmt(std::unique_ptr<ASTNode> e) : expr(std::move(e)) {}

    std::string ReturnStmt::print() const {
        return "ReturnStmt(" + (expr ? expr->print() : "null") + ")";
    }

    llvm::Value* ReturnStmt::codegen(llvm::LLVMContext& context) {
        llvm::Value* retVal = expr ? expr->codegen(context) : nullptr;
        llvm::IRBuilder<> builder(context);
        return builder.CreateRet(retVal);
    }

} // namespace infine