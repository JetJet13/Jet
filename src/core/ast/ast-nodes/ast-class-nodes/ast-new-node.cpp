//
// Created by Johny Georges on 2024-04-26.
//

#include "ast-new-node.h"

ASTNodeType ASTNewNode::getNodeType() {
    return AST_NEW_NODE;
}

std::string ASTNewNode::toString() {
    return "NEW";
}