// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 最后修改：2026-08-13
// -----------------------------------------------------------------------------

#include "IntegerLiteral.h"
#include <llvm-c/Core.h>

namespace infine {

    IntegerLiteral::IntegerLiteral(int val) : value(val) {}

    std::string IntegerLiteral::print() const {
        return "IntegerLiteral(" + std::to_string(value) + ")";
    }

    // 生成一个常量整数 IR 值
    // Generates a constant integer IR value
    LLVMValueRef IntegerLiteral::codegen(LLVMModuleRef module, LLVMBuilderRef builder) {
        LLVMContextRef context = LLVMGetModuleContext(module);
        return LLVMConstInt(LLVMInt32TypeInContext(context), value, 0);
    }

    int IntegerLiteral::getValue() const {
        return value;
    }

} // namespace infine