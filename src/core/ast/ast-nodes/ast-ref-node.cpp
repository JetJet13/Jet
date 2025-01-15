//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-ref-node.h"

ASTNodeType ASTRefNode::getNodeType() {
    return AST_REF_NODE;
}

std::string ASTRefNode::toString() {
    return "REF";
}