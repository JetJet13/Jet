//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-inequality-operator-node.h"

ASTNodeType ASTInequalityOperatorNode::getNodeType() {
    return AST_INEQUALITY_OPERATOR_NODE;
}

std::string ASTInequalityOperatorNode::toString() {
    return "INEQUALITY_OPERATOR";
}