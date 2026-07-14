//
// Created by Johny Georges on 2026-07-11.
//

#include "ast-shared-node.h"

ASTNodeType ASTSharedNode::getNodeType() {
    return AST_SHARED_NODE;
}

std::string ASTSharedNode::toString() {
    return "SHARED";
}