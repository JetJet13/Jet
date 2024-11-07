//
// Created by Johny Georges on 2024-11-07.
//

#include "ast-callable-identifier-expression-node.h"

ASTNodeType ASTCallableIdentifierExpressionNode::getNodeType() {
    return AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE;
}

std::string ASTCallableIdentifierExpressionNode::toString() {
    return "CALLABLE_IDENTIFIER_EXPRESSION";
}