// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.1
// 日期：2026-07-28
// 路径：ICC/src/token/Token.h
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <unordered_map>

namespace infine {

    enum class TokenType {
        KEYWORD_FUNC,
        KEYWORD_VAR,
        KEYWORD_IF,
        KEYWORD_ELSE,
        KEYWORD_RETURN,
        KEYWORD_FOR,
        KEYWORD_WHILE,
        KEYWORD_BREAK,
        KEYWORD_CONTINUE,

        IDENTIFIER,
        INT_LITERAL,
        FLOAT_LITERAL,
        STRING_LITERAL,
        CHAR_LITERAL,

        OPERATOR,
        SYMBOL,
        END_OF_FILE,
        UNKNOWN
    };

    struct Token {
        TokenType type;
        std::string lexeme;
        int line;
        int column;

        std::string typeName() const;
    };

    extern const std::unordered_map<TokenType, std::string> TokenTypeNames;

} // namespace infine