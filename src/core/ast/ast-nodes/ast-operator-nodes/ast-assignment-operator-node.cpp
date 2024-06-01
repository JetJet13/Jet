//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-assignment-operator-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTAssignmentOperatorNode::getNodeType() {
    return AST_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTAssignmentOperatorNode::toString() {
    return "ASSIGNMENT_OPERATOR";
}