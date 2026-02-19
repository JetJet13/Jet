//
// Created by Johny Georges on 2026-02-16.
//

#include "ast-ref-value-assignment-operator-node.h"

ASTNodeType ASTRefValueAssignmentOperatorNode::getNodeType() {
    return AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTRefValueAssignmentOperatorNode::toString() {
    return "REF_VALUE_ASSIGNMENT_OPERATOR";
}