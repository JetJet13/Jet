//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-plus-operator-node.h"

ASTNodeType ASTPlusOperatorNode::getNodeType() {
    return AST_PLUS_OPERATOR_NODE;
}

std::string ASTPlusOperatorNode::toString() {
    return "PLUS_OPERATOR";
}