//
// Created by Johny Georges on 2024-06-21.
//

#include "ast-struct-colon-node.h"

ASTNodeType ASTStructColonNode::getNodeType() {
    return AST_STRUCT_COLON_NODE;
}

std::string ASTStructColonNode::toString() {
    return "STRUCT_COLON";
}