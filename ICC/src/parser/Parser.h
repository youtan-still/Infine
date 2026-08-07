// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.2
// 日期：2026-08-01
// -----------------------------------------------------------------------------

#pragma once
#include <vector>
#include <memory>
#include "../token/Token.h"
#include "../ast/ASTNode.h"
#include "../ast/BlockStmt.h"   // 新增

namespace infine {

    class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);
        std::unique_ptr<ASTNode> parseProgram();

    private:
        std::vector<Token> tokens;
        size_t pos = 0;

        Token peek() const;
        Token previous() const;
        Token advance();
        bool isAtEnd() const;
        Token consume(TokenType type, const std::string& message);

        std::unique_ptr<ASTNode> parseFunction();
        std::unique_ptr<BlockStmt> parseBlock();   // 返回类型改为 BlockStmt
        std::unique_ptr<ASTNode> parseStatement();
        std::unique_ptr<ASTNode> parseExpression();
        std::unique_ptr<ASTNode> parsePrimary();
    };

} // namespace infine