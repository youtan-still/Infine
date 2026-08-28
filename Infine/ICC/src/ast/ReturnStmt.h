// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include <memory>

namespace infine {

    // return 语句节点，包含一个可选的返回表达式
    // Return statement node, optionally containing a return expression
    class ReturnStmt : public ASTNode {
    public:
        explicit ReturnStmt(std::unique_ptr<ASTNode> expr);

        std::string print() const override;
        LLVMValueRef codegen(LLVMModuleRef module, LLVMBuilderRef builder) override;

    private:
        std::unique_ptr<ASTNode> expr;
    };

} // namespace infine