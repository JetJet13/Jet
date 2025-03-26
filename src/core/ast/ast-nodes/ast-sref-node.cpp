//
// Created by Johny Georges on 2025-03-26.
//

#include "ast-sref-node.h"

ASTNodeType ASTSrefNode::getNodeType() {
    return AST_SREF_NODE;
}

std::string ASTSrefNode::toString() {
    return "SREF";
}