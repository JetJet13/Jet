//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-dref-node.h"

ASTNodeType ASTDrefNode::getNodeType() {
    return AST_DREF_NODE;
}

std::string ASTDrefNode::toString() {
    return "DREF";
}