// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.3
// 日期：2026-08-02
// 路径：ICC/src/ast/FunctionDecl.h
// -----------------------------------------------------------------------------

#pragma once
#include "ASTNode.h"
#include "BlockStmt.h"
#include <string>
#include <memory>
#include <llvm/IR/Module.h>

namespace infine {

    // 函数声明节点
    class FunctionDecl : public ASTNode {
    public:
        FunctionDecl(std::string name, std::string returnType,
            std::unique_ptr<BlockStmt> body);
        std::string print() const override;
        llvm::Value* codegen(llvm::LLVMContext& context) override;

        // 获取 LLVM Module（用于输出 IR）
        llvm::Module* getModule() const { return module; }

    private:
        std::string name;
        std::string returnType;
        std::unique_ptr<BlockStmt> body;
        llvm::Module* module = nullptr;
    };

} // namespace infine