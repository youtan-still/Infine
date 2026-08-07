// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.1
// 日期：2026-07-28
// 路径：ICC/src/lexer/Lexer.cpp
// -----------------------------------------------------------------------------

#include "Lexer.h"
#include <cctype>
#include <unordered_map>

namespace infine {

    static const std::unordered_map<std::string, TokenType> keywordMap = {
        {"func",     TokenType::KEYWORD_FUNC},
        {"var",      TokenType::KEYWORD_VAR},
        {"if",       TokenType::KEYWORD_IF},
        {"else",     TokenType::KEYWORD_ELSE},
        {"return",   TokenType::KEYWORD_RETURN},
        {"for",      TokenType::KEYWORD_FOR},
        {"while",    TokenType::KEYWORD_WHILE},
        {"break",    TokenType::KEYWORD_BREAK},
        {"continue", TokenType::KEYWORD_CONTINUE}
    };

    Lexer::Lexer(std::string_view src) : source(src) {}

    bool Lexer::isAtEnd() const {
        return pos >= source.size();
    }

    char Lexer::current() const {
        return isAtEnd() ? '\0' : source[pos];
    }

    void Lexer::advance() {
        if (!isAtEnd()) {
            if (current() == '\n') {
                line++;
                column = 1;
            }
            else {
                column++;
            }
            pos++;
        }
    }

    void Lexer::skipWhitespace() {
        while (!isAtEnd() && std::isspace(static_cast<unsigned char>(current()))) {
            advance();
        }
    }

    void Lexer::skipComment() {
        if (current() == '/' && pos + 1 < source.size()) {
            char next = source[pos + 1];
            if (next == '/') {
                while (!isAtEnd() && current() != '\n') {
                    advance();
                }
                return;
            }
            else if (next == '*') {
                advance();
                advance();
                while (!isAtEnd() && !(current() == '*' && pos + 1 < source.size() && source[pos + 1] == '/')) {
                    advance();
                }
                if (!isAtEnd()) {
                    advance();
                    advance();
                }
                return;
            }
        }
    }

    Token Lexer::makeToken(TokenType type, std::string lexeme) {
        return Token{ type, std::move(lexeme), line, column - static_cast<int>(lexeme.size()) };
    }

    Token Lexer::readIdentifier() {
        size_t start = pos;
        while (!isAtEnd() && (std::isalnum(static_cast<unsigned char>(current())) || current() == '_')) {
            advance();
        }
        std::string word(source.substr(start, pos - start));
        auto it = keywordMap.find(word);
        TokenType type = (it != keywordMap.end()) ? it->second : TokenType::IDENTIFIER;
        return makeToken(type, word);
    }

    Token Lexer::readNumber() {
        size_t start = pos;
        bool isFloat = false;
        while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(current()))) {
            advance();
        }
        if (!isAtEnd() && current() == '.') {
            isFloat = true;
            advance();
            while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(current()))) {
                advance();
            }
        }
        std::string number(source.substr(start, pos - start));
        return makeToken(isFloat ? TokenType::FLOAT_LITERAL : TokenType::INT_LITERAL, number);
    }

    Token Lexer::readString() {
        advance();
        size_t start = pos;
        while (!isAtEnd() && current() != '"') {
            if (current() == '\\') {
                advance();
                if (!isAtEnd()) advance();
            }
            else {
                advance();
            }
        }
        std::string str(source.substr(start, pos - start));
        if (!isAtEnd()) advance();
        return makeToken(TokenType::STRING_LITERAL, str);
    }

    Token Lexer::readChar() {
        advance();
        char ch = current();
        advance();
        if (!isAtEnd() && current() == '\'') advance();
        return makeToken(TokenType::CHAR_LITERAL, std::string(1, ch));
    }

    Token Lexer::readOperatorOrSymbol() {
        char ch = current();
        advance();

        if ((ch == '>' || ch == '<' || ch == '=' || ch == '!' || ch == '&' || ch == '|') &&
            !isAtEnd() && current() == '=') {
            std::string op = { ch, '=' };
            advance();
            return makeToken(TokenType::OPERATOR, op);
        }
        if (ch == '&' && !isAtEnd() && current() == '&') {
            advance();
            return makeToken(TokenType::OPERATOR, "&&");
        }
        if (ch == '|' && !isAtEnd() && current() == '|') {
            advance();
            return makeToken(TokenType::OPERATOR, "||");
        }

        if (strchr("{}()[];,", ch)) {
            return makeToken(TokenType::SYMBOL, std::string(1, ch));
        }
        return makeToken(TokenType::OPERATOR, std::string(1, ch));
    }

    std::vector<Token> Lexer::tokenize() {
        std::vector<Token> tokens;
        while (!isAtEnd()) {
            skipWhitespace();
            if (isAtEnd()) break;

            if (current() == '/') {
                size_t saved = pos;
                skipComment();
                if (pos > saved) continue;
            }

            char ch = current();
            if (std::isalpha(static_cast<unsigned char>(ch)) || ch == '_') {
                tokens.push_back(readIdentifier());
            }
            else if (std::isdigit(static_cast<unsigned char>(ch))) {
                tokens.push_back(readNumber());
            }
            else if (ch == '"') {
                tokens.push_back(readString());
            }
            else if (ch == '\'') {
                tokens.push_back(readChar());
            }
            else {
                tokens.push_back(readOperatorOrSymbol());
            }
        }
        tokens.push_back(makeToken(TokenType::END_OF_FILE, ""));
        return tokens;
    }

} // namespace infine