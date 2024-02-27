//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-minus-operator-node.h"

ASTNodeType ASTMinusOperatorNode::getNodeType() {
    return AST_MINUS_OPERATOR_NODE;
}

std::string ASTMinusOperatorNode::toString() {
    return "MINUS_OPERATOR";
}