// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.1
// 日期：2026-07-28
// 路径：ICC/src/lexer/Lexer.h
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include "../token/Token.h"

namespace infine {

    class Lexer {
    public:
        explicit Lexer(std::string_view source);
        std::vector<Token> tokenize();

    private:
        std::string_view source;
        size_t pos = 0;
        int line = 1;
        int column = 1;

        char current() const;
        void advance();
        bool isAtEnd() const;
        void skipWhitespace();
        void skipComment();

        Token makeToken(TokenType type, std::string lexeme);
        Token readIdentifier();
        Token readNumber();
        Token readString();
        Token readChar();
        Token readOperatorOrSymbol();
    };

} // namespace infine