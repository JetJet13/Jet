//
// Created by Johny Georges on 2024-11-07.
//

#ifndef JETLANG_AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE_H

#include "ast-identifier-expression-node.h"

class ASTCallableIdentifierExpressionNode : public ASTIdentifierExpressionNode {
    using ASTIdentifierExpressionNode::ASTIdentifierExpressionNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE_H
