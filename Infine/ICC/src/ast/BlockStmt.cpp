// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#include "BlockStmt.h"
#include <llvm-c/Core.h>

namespace infine {

    void BlockStmt::addStatement(std::unique_ptr<ASTNode> stmt) {
        statements.push_back(std::move(stmt));
    }

    std::string BlockStmt::print() const {
        std::string result = "BlockStmt(";
        for (const auto& stmt : statements) {
            result += stmt->print() + " ";
        }
        result += ")";
        return result;
    }

    // 依次生成每条语句的 IR，返回最后一条语句的值
    // Generates IR for each statement sequentially, returns the last value
    LLVMValueRef BlockStmt::codegen(LLVMModuleRef module, LLVMBuilderRef builder) {
        LLVMValueRef last = nullptr;
        for (auto& stmt : statements) {
            last = stmt->codegen(module, builder);
        }
        return last;
    }

} // namespace infine