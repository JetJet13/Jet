//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-private-node.h"

ASTNodeType ASTPrivateNode::getNodeType() {
    return AST_PRIVATE_NODE;
}

std::string ASTPrivateNode::toString() {
    return "PRIVATE";
}