// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-09-25
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include <vector>
#include <memory>

namespace infine {

    // 程序顶层容器节点，包含多个函数声明
    // Program top-level container node, containing multiple function declarations
    class ProgramDecl : public ASTNode {
    public:
        // 添加一个函数声明到程序中
        // Adds a function declaration to the program
        void addFunction(std::unique_ptr<ASTNode> func);

        std::string print() const override;

        // 依次为每个函数生成 IR，返回最后一个函数的值
        // Generates IR for each function sequentially, returns the last function's value
        LLVMValueRef codegen(LLVMModuleRef module, LLVMBuilderRef builder) override;

    private:
        std::vector<std::unique_ptr<ASTNode>> functions;
    };

} // namespace infine