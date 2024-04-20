//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-this-access-node.h"

ASTNodeType ASTThisAccessNode::getNodeType() {
    return AST_THIS_ACCESS_NODE;
}

std::string ASTThisAccessNode::toString() {
    return "THIS_ACCESS";
}