// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"

namespace infine {

    // 整数字面量节点，存储一个整数值
    // Integer literal node, stores an integer value
    class IntegerLiteral : public ASTNode {
    public:
        explicit IntegerLiteral(int value);

        std::string print() const override;
        LLVMValueRef codegen(LLVMModuleRef module, LLVMBuilderRef builder) override;

        // 返回存储的整数值
        // Returns the stored integer value
        int getValue() const;

    private:
        int value;
    };

} // namespace infine