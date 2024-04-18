//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-public-node.h"

ASTNodeType ASTPublicNode::getNodeType() {
    return AST_PUBLIC_NODE;
}

std::string ASTPublicNode::toString() {
    return "PUBLIC";
}