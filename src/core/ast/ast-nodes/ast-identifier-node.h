//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_IDENTIFIER_NODE_H
#define JETLANG_AST_IDENTIFIER_NODE_H

#include "../../lexeme/lexeme.h"
#include "ast-node.h"

class ASTIdentifierNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTIdentifierNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    std::string getValue(TokenTable* tokenTable);
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IDENTIFIER_NODE_H
