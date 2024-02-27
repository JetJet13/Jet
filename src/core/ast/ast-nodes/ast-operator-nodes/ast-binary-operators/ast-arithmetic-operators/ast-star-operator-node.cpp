//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-star-operator-node.h"

ASTNodeType ASTStarOperatorNode::getNodeType() {
    return AST_STAR_OPERATOR_NODE;
}

std::string ASTStarOperatorNode::toString() {
    return "STAR_OPERATOR";
}