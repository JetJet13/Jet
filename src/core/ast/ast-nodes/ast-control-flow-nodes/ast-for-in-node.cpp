//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-node.h"

ASTNodeType ASTForInNode::getNodeType() {
    return AST_FOR_IN_NODE;
}

std::string ASTForInNode::toString() {
    return "FOR_IN";
}