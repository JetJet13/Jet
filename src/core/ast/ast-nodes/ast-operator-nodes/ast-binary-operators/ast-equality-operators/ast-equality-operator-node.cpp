//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-equality-operator-node.h"

ASTNodeType ASTEqualityOperatorNode::getNodeType() {
    return AST_EQUALITY_OPERATOR_NODE;
}

std::string ASTEqualityOperatorNode::toString() {
    return "EQUALITY_OPERATOR";
}