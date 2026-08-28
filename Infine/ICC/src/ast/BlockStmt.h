// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include <vector>
#include <memory>

namespace infine {

    // 语句块节点，包含一组有序的语句
    // Block node containing an ordered list of statements
    class BlockStmt : public ASTNode {
    public:
        // 向块中添加一条语句
        // Adds a statement to the block
        void addStatement(std::unique_ptr<ASTNode> stmt);

        std::string print() const override;
        LLVMValueRef codegen(LLVMModuleRef module, LLVMBuilderRef builder) override;

    private:
        std::vector<std::unique_ptr<ASTNode>> statements;
    };

} // namespace infine