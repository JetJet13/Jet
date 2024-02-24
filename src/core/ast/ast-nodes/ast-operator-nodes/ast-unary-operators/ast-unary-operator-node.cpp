//
// Created by Johny Georges on 2024-02-20.
//

#include "./ast-unary-operator-node.h"

ASTNodeType ASTUnaryOperatorNode::getNodeType() {
    return AST_UNARY_OPERATOR_NODE;
}

std::string ASTUnaryOperatorNode::toString() {
    return "UNARY_OPERATOR";
}