//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-struct-start-node.h"

ASTNodeType ASTStructStartNode::getNodeType() {
    return AST_STRUCT_START_NODE;
}

std::string ASTStructStartNode::toString() {
    return "STRUCT_START";
}