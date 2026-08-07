// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/ReturnStmt.cpp
// -----------------------------------------------------------------------------

#include "ReturnStmt.h"

namespace infine {

    ReturnStmt::ReturnStmt(std::unique_ptr<ASTNode> e) : expr(std::move(e)) {}

    std::string ReturnStmt::print() const {
        return "ReturnStmt(" + (expr ? expr->print() : "null") + ")";
    }

} // namespace infine