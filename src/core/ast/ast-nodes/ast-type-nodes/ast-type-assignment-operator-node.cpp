//
// Created by Johny Georges on 2025-07-07.
//

#include "ast-type-assignment-operator-node.h"

ASTNodeType ASTTypeAssignmentOperatorNode::getNodeType() {
    return AST_TYPE_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTTypeAssignmentOperatorNode::toString() {
    return "TYPE_ASSIGNMENT_OPERATOR";
}