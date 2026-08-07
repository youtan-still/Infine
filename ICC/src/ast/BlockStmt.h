// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.3
// 日期：2026-08-02
// 路径：ICC/src/ast/BlockStmt.h
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include <vector>
#include <memory>

namespace infine {

    // 代码块节点
    class BlockStmt : public ASTNode {
    public:
        void addStatement(std::unique_ptr<ASTNode> stmt);
        std::string print() const override;
        llvm::Value* codegen(llvm::LLVMContext& context) override;

    private:
        std::vector<std::unique_ptr<ASTNode>> statements;
    };

} // namespace infine