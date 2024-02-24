//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-less-than-or-equal-operator-node.h"

ASTLessThanOrEqualOperatorNode::ASTLessThanOrEqualOperatorNode(Lexeme *lexeme) {
    _lessThanOrEqual = lexeme;
}

ASTNodeType ASTLessThanOrEqualOperatorNode::getNodeType() {
    return AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE;
}

std::string ASTLessThanOrEqualOperatorNode::toString() {
    return "LESS_THAN_OR_EQUAL";
}
