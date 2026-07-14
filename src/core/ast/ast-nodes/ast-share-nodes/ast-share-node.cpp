//
// Created by Johny Georges on 2026-07-11.
//

#include "ast-share-node.h"

ASTNodeType ASTShareNode::getNodeType() {
    return AST_SHARE_NODE;
}

std::string ASTShareNode::toString() {
    return "SHARE";
}