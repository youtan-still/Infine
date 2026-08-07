// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/IntegerLiteral.cpp
// -----------------------------------------------------------------------------

#include "IntegerLiteral.h"

namespace infine {

    IntegerLiteral::IntegerLiteral(int val) : value(val) {}

    std::string IntegerLiteral::print() const {
        return "IntegerLiteral(" + std::to_string(value) + ")";
    }

    int IntegerLiteral::getValue() const {
        return value;
    }

} // namespace infine