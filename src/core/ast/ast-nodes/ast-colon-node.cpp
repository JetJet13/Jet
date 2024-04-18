//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-colon-node.h"

ASTNodeType ASTColonNode::getNodeType() {
    return AST_COLON_NODE;
}

std::string ASTColonNode::toString() {
    return "COLON";
}