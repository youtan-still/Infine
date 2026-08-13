// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#pragma once
#include <string>
#include <llvm-c/Core.h>

namespace infine {

    // 抽象语法树节点的基类，所有 AST 节点均继承自此类
    // Base class for all abstract syntax tree nodes
    class ASTNode {
    public:
        virtual ~ASTNode() = default;

        // 将节点转换为可读字符串（用于调试）
        // Converts node to a human-readable string (for debugging)
        virtual std::string print() const = 0;

        // 生成 LLVM IR，返回生成的 LLVM 值
        // Generates LLVM IR and returns the generated LLVM value
        virtual LLVMValueRef codegen(LLVMModuleRef module, LLVMBuilderRef builder) = 0;
    };

} // namespace infine