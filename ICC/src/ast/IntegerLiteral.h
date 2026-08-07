// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/IntegerLiteral.h
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"

namespace infine {

    // 整数字面量节点
    class IntegerLiteral : public ASTNode {
    public:
        explicit IntegerLiteral(int value);
        std::string print() const override;
        int getValue() const;

    private:
        int value;
    };

} // namespace infine