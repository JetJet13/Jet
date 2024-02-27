//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-greater-than-operator-node.h"

ASTNodeType ASTGreaterThanOperatorNode::getNodeType() {
    return AST_GREATER_THAN_OPERATOR_NODE;
}

std::string ASTGreaterThanOperatorNode::toString() {
    return "GREATER_THAN";
}