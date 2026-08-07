// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.3
// 日期：2026-08-02
// 路径：ICC/src/ast/ASTNode.h
// -----------------------------------------------------------------------------

#pragma once
#include <string>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>

namespace infine {

    // 抽象语法树节点基类
    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual std::string print() const = 0;

        // 生成 LLVM IR，传入 LLVMContext 引用
        virtual llvm::Value* codegen(llvm::LLVMContext& context) = 0;
    };

} // namespace infine