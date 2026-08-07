// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// -----------------------------------------------------------------------------

#include "Parser.h"
#include "../ast/IntegerLiteral.h"
#include "../ast/ReturnStmt.h"
#include "../ast/BlockStmt.h"
#include "../ast/FunctionDecl.h"
#include <iostream>
#include <stdexcept>

namespace infine {

    Parser::Parser(const std::vector<Token>& tok) : tokens(tok), pos(0) {}

    bool Parser::isAtEnd() const {
        return pos >= tokens.size() || tokens[pos].type == TokenType::END_OF_FILE;
    }

    Token Parser::peek() const {
        if (isAtEnd()) return Token{ TokenType::END_OF_FILE, "", 0, 0 };
        return tokens[pos];
    }

    Token Parser::previous() const {
        if (pos == 0) return Token{ TokenType::END_OF_FILE, "", 0, 0 };
        return tokens[pos - 1];
    }

    Token Parser::advance() {
        if (!isAtEnd()) pos++;
        return previous();
    }

    Token Parser::consume(TokenType type, const std::string& message) {
        if (peek().type == type) return advance();
        throw std::runtime_error(message + " at " + std::to_string(peek().line) +
            ":" + std::to_string(peek().column));
    }

    std::unique_ptr<ASTNode> Parser::parseProgram() {
        return parseFunction();
    }

    std::unique_ptr<ASTNode> Parser::parseFunction() {
        consume(TokenType::KEYWORD_FUNC, "Expected 'func'");
        consume(TokenType::IDENTIFIER, "Expected return type");
        std::string returnType = previous().lexeme;
        consume(TokenType::IDENTIFIER, "Expected function name");
        std::string funcName = previous().lexeme;
        consume(TokenType::SYMBOL, "Expected '('");
        consume(TokenType::SYMBOL, "Expected ')'");
        auto body = parseBlock();   // 现在直接得到 BlockStmt
        return std::make_unique<FunctionDecl>(funcName, returnType, std::move(body));
    }

    std::unique_ptr<BlockStmt> Parser::parseBlock() {
        consume(TokenType::SYMBOL, "Expected '{'");
        auto block = std::make_unique<BlockStmt>();
        while (peek().type != TokenType::SYMBOL || peek().lexeme != "}") {
            if (isAtEnd()) {
                throw std::runtime_error("Unclosed block at " +
                    std::to_string(peek().line) + ":" +
                    std::to_string(peek().column));
            }
            auto stmt = parseStatement();
            if (stmt) block->addStatement(std::move(stmt));
        }
        consume(TokenType::SYMBOL, "Expected '}'");
        return block;
    }

    std::unique_ptr<ASTNode> Parser::parseStatement() {
        if (peek().type == TokenType::KEYWORD_RETURN) {
            advance();
            auto expr = parseExpression();
            consume(TokenType::SYMBOL, "Expected ';'");
            return std::make_unique<ReturnStmt>(std::move(expr));
        }
        throw std::runtime_error("Unexpected token at " +
            std::to_string(peek().line) + ":" +
            std::to_string(peek().column));
    }

    std::unique_ptr<ASTNode> Parser::parseExpression() {
        return parsePrimary();
    }

    std::unique_ptr<ASTNode> Parser::parsePrimary() {
        if (peek().type == TokenType::INT_LITERAL) {
            int value = std::stoi(peek().lexeme);
            advance();
            return std::make_unique<IntegerLiteral>(value);
        }
        throw std::runtime_error("Expected expression at " +
            std::to_string(peek().line) + ":" +
            std::to_string(peek().column));
    }

} // namespace infine