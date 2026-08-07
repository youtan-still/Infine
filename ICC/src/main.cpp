// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// -----------------------------------------------------------------------------

#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"

int main() {
    std::cout << "Infine Code Compiler 0.0.2\n\n";

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

    infine::Parser parser(tokens);
    try {
        auto ast = parser.parseProgram();
        if (ast) {
            std::cout << "\nAST:\n" << ast->print() << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "\nParse error: " << e.what() << "\n";
    }

    std::cin.get();
    return 0;
}