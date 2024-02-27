//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-bang-operator-node.h"

ASTNodeType ASTBangOperatorNode::getNodeType() {
    return AST_BANG_OPERATOR_NODE;
}

std::string ASTBangOperatorNode::toString() {
    return "BANG_OPERATOR";
}
