// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/ReturnStmt.h
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include <memory>

namespace infine {

    // return 语句节点
    class ReturnStmt : public ASTNode {
    public:
        explicit ReturnStmt(std::unique_ptr<ASTNode> expr);
        std::string print() const override;

    private:
        std::unique_ptr<ASTNode> expr;
    };

} // namespace infine