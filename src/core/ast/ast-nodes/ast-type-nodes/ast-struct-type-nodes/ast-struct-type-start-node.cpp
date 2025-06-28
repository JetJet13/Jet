//
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-start-node.h"

ASTNodeType ASTStructTypeStartNode::getNodeType() {
    return AST_STRUCT_TYPE_START_NODE;
}

std::string ASTStructTypeStartNode::toString() {
    return "STRUCT_TYPE_START";
}