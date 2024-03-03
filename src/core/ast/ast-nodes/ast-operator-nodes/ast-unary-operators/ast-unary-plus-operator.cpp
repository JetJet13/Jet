//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-unary-plus-operator.h"

ASTNodeType ASTUnaryPlusOperatorNode::getNodeType() {
    return AST_UNARY_PLUS_OPERATOR_NODE;
}

std::string ASTUnaryPlusOperatorNode::toString() {
    return "UNARY_PLUS_OPERATOR (" + _lexemeOperator->toString() + ")";
}