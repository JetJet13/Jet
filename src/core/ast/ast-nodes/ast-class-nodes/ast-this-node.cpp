//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-this-node.h"

ASTNodeType ASTThisNode::getNodeType() {
    return AST_THIS_NODE;
}

std::string ASTThisNode::toString() {
    return "THIS";
}