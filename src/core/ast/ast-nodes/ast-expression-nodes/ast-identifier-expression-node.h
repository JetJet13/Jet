//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_AST_IDENTIFIER_EXPRESSION_NODE_H

#include "../ast-identifier-node.h"
#include "ast-expression-node.h"

class ASTIdentifierExpressionNode : public ASTExpressionNode {
private:
    ASTIdentifierNode* _identifierNode;
public:
    ASTIdentifierExpressionNode(ASTIdentifierNode* identifierNode);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_IDENTIFIER_EXPRESSION_NODE_H
