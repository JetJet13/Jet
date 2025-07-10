//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-void-node.h"

ASTNodeType ASTVoidNode::getNodeType() {
    return AST_VOID_NODE;
}

std::string ASTVoidNode::toString() {
    return "VOID";
}