// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// 路径：ICC/src/ast/FunctionDecl.cpp
// -----------------------------------------------------------------------------

#include "FunctionDecl.h"

namespace infine {

    FunctionDecl::FunctionDecl(std::string n, std::string rt,
        std::unique_ptr<BlockStmt> b)
        : name(std::move(n)), returnType(std::move(rt)), body(std::move(b)) {
    }

    std::string FunctionDecl::print() const {
        return "FunctionDecl(" + name + ", " + returnType + ", " +
            (body ? body->print() : "null") + ")";
    }

} // namespace infine