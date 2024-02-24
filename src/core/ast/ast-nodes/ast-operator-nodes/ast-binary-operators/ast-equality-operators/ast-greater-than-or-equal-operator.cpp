//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-greater-than-or-equal-operator.h"

ASTGreaterThanOrEqualOperatorNode::ASTGreaterThanOrEqualOperatorNode(Lexeme *lexeme) {
    _greaterThanOrEqual = lexeme;
}

ASTNodeType ASTGreaterThanOrEqualOperatorNode::getNodeType() {
    return AST_GREATER_THAN_OR_EQUAL_OPERATOR_NODE;
}

std::string ASTGreaterThanOrEqualOperatorNode::toString() {
    return "GREATER_THAN_OR_EQUAL";
}