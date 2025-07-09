//
// Created by Johny Georges on 2025-07-08.
//

#include "ast-array-type-end-node.h"

ASTNodeType ASTArrayTypeEndNode::getNodeType() {
    return AST_ARRAY_TYPE_END_NODE;
}

std::string ASTArrayTypeEndNode::toString() {
    return "ARRAY_TYPE_END";
}