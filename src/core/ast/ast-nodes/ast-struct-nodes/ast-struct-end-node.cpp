//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-struct-end-node.h"

ASTNodeType ASTStructEndNode::getNodeType() {
    return AST_STRUCT_END_NODE;
}

std::string ASTStructEndNode::toString() {
    return "STRUCT_END";
}