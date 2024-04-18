//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-static-node.h"

ASTNodeType ASTStaticNode::getNodeType() {
    return AST_STATIC_NODE;
}

std::string ASTStaticNode::toString() {
    return "STATIC";
}