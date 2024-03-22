//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_IDENTIFIER_NODE_H
#define JETLANG_AST_IDENTIFIER_NODE_H

#include "../../lexeme/lexeme.h"
#include "ast-node.h"

class ASTIdentifierNode : public ASTNode {
private:
    Lexeme* _identifier;
public:
    ASTIdentifierNode(Lexeme* lexeme);
    Lexeme* getIdentifier();
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IDENTIFIER_NODE_H
