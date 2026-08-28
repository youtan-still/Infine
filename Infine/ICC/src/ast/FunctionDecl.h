// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include "BlockStmt.h"
#include <string>
#include <memory>

namespace infine {

    // 函数声明节点，包含函数名、返回类型和函数体
    // Function declaration node, containing name, return type, and body
    class FunctionDecl : public ASTNode {
    public:
        FunctionDecl(std::string name, std::string returnType,
            std::unique_ptr<BlockStmt> body);

        std::string print() const override;
        LLVMValueRef codegen(LLVMModuleRef module, LLVMBuilderRef builder) override;

        // 返回当前模块（供外部使用）
        // Returns the current module (for external use)
        LLVMModuleRef getModule() const { return module; }

    private:
        std::string name;
        std::string returnType;
        std::unique_ptr<BlockStmt> body;
        LLVMModuleRef module = nullptr;
    };

} // namespace infine