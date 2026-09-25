// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-09-25
// -----------------------------------------------------------------------------

#include "ProgramDecl.h"
#include <llvm-c/Core.h>

namespace infine {

    void ProgramDecl::addFunction(std::unique_ptr<ASTNode> func) {
        functions.push_back(std::move(func));
    }

    std::string ProgramDecl::print() const {
        std::string result = "ProgramDecl(";
        for (const auto& func : functions) {
            result += func->print() + " ";
        }
        result += ")";
        return result;
    }

    LLVMValueRef ProgramDecl::codegen(LLVMModuleRef module, LLVMBuilderRef builder) {
        LLVMValueRef last = nullptr;
        for (auto& func : functions) {
            last = func->codegen(module, builder);
        }
        return last;
    }

} // namespace infine