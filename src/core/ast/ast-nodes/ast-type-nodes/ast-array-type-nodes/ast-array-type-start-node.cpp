//
// Created by Johny Georges on 2025-07-08.
//

#include "ast-array-type-start-node.h"

ASTNodeType ASTArrayTypeStartNode::getNodeType() {
    return AST_ARRAY_TYPE_START_NODE;
}

std::string ASTArrayTypeStartNode::toString() {
    return "ARRAY_TYPE_START";
}