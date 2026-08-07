// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.1
// 日期：2026-07-28
// 路径：ICC/src/main.cpp
// -----------------------------------------------------------------------------

#include <iostream>
#include "lexer/Lexer.h"

int main() {
    std::cout << "Infine Code Compiler 0.0.1\n\n";

    std::string code = R"(
        func int main() {
            return 0;
        }
    )";

    infine::Lexer lexer(code);
    auto tokens = lexer.tokenize();

    for (const auto& tok : tokens) {
        std::cout << "[" << tok.typeName() << "] \""
            << tok.lexeme << "\" at " << tok.line << ":" << tok.column << "\n";
    }
    std::cin.get();
    return 0;
}