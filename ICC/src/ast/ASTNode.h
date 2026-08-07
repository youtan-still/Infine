// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/ASTNode.h
// -----------------------------------------------------------------------------

#pragma once
#include <string>

namespace infine {

    // 抽象语法树节点基类
    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual std::string print() const = 0;
    };

} // namespace infine