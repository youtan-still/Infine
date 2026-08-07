// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/BlockStmt.cpp
// -----------------------------------------------------------------------------

#include "BlockStmt.h"

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

} // namespace infine