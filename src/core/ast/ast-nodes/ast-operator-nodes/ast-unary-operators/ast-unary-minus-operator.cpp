//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-unary-minus-operator.h"


ASTNodeType ASTUnaryMinusOperatorNode::getNodeType() {
    return AST_UNARY_MINUS_OPERATOR_NODE;
}

std::string ASTUnaryMinusOperatorNode::toString() {
    return "UNARY_MINUS_OPERATOR";
}
