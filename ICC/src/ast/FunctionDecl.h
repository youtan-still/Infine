// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/FunctionDecl.h
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include "BlockStmt.h"
#include <string>
#include <memory>

namespace infine {

    // 函数声明节点
    class FunctionDecl : public ASTNode {
    public:
        FunctionDecl(std::string name, std::string returnType,
            std::unique_ptr<BlockStmt> body);
        std::string print() const override;

    private:
        std::string name;
        std::string returnType;
        std::unique_ptr<BlockStmt> body;
    };

} // namespace infine