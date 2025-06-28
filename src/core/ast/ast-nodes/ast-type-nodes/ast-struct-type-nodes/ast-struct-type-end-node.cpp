//
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-end-node.h"

ASTNodeType ASTStructTypeEndNode::getNodeType() {
    return AST_STRUCT_TYPE_END_NODE;
}

std::string ASTStructTypeEndNode::toString() {
    return "STRUCT_TYPE_END";
}