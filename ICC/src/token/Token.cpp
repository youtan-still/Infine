// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.1
// 日期：2026-07-28
// 路径：ICC/src/token/Token.cpp
// -----------------------------------------------------------------------------

#include "Token.h"

namespace infine {

    const std::unordered_map<TokenType, std::string> TokenTypeNames = {
        {TokenType::KEYWORD_FUNC,     "func"},
        {TokenType::KEYWORD_VAR,      "var"},
        {TokenType::KEYWORD_IF,       "if"},
        {TokenType::KEYWORD_ELSE,     "else"},
        {TokenType::KEYWORD_RETURN,   "return"},
        {TokenType::KEYWORD_FOR,      "for"},
        {TokenType::KEYWORD_WHILE,    "while"},
        {TokenType::KEYWORD_BREAK,    "break"},
        {TokenType::KEYWORD_CONTINUE, "continue"},
        {TokenType::IDENTIFIER,       "identifier"},
        {TokenType::INT_LITERAL,      "int_literal"},
        {TokenType::FLOAT_LITERAL,    "float_literal"},
        {TokenType::STRING_LITERAL,   "string_literal"},
        {TokenType::CHAR_LITERAL,     "char_literal"},
        {TokenType::OPERATOR,         "operator"},
        {TokenType::SYMBOL,           "symbol"},
        {TokenType::END_OF_FILE,      "EOF"},
        {TokenType::UNKNOWN,          "unknown"}
    };

    std::string Token::typeName() const {
        auto it = TokenTypeNames.find(type);
        return (it != TokenTypeNames.end()) ? it->second : "???";
    }

} // namespace infine