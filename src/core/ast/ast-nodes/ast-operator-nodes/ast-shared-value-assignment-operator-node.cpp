//
// Created by Johny Georges on 2026-02-16.
//

#include "ast-shared-value-assignment-operator-node.h"

ASTNodeType ASTSharedValueAssignmentOperatorNode::getNodeType() {
    return AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTSharedValueAssignmentOperatorNode::toString() {
    return "SHARED_VALUE_ASSIGNMENT_OPERATOR";
}