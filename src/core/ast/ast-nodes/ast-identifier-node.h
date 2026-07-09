//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_IDENTIFIER_NODE_H
#define JETLANG_AST_IDENTIFIER_NODE_H

#include "../../lexeme/lexeme.h"
#include "ast-node.h"

class ASTIdentifierNode : public ASTNode {
private:
    std::shared_ptr<Lexeme> _lexeme;
public:
    explicit ASTIdentifierNode(std::shared_ptr<Lexeme> lexeme);
    std::shared_ptr<Lexeme> getLexeme();
    std::string getValue(TokenTable* tokenTable);
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IDENTIFIER_NODE_H
