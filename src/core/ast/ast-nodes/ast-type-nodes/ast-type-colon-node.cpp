//
// Created by Johny Georges on 2024-06-22.
//

#include "ast-type-colon-node.h"

ASTNodeType ASTTypeColonNode::getNodeType() {
    return AST_TYPE_COLON_NODE;
}

std::string ASTTypeColonNode::toString() {
    return "TYPE_COLON";
}