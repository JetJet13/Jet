//
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-colon-node.h"

ASTNodeType ASTStructTypeColonNode::getNodeType() {
    return AST_STRUCT_TYPE_COLON_NODE;
}

std::string ASTStructTypeColonNode::toString() {
    return "STRUCT_TYPE_COLON";
}