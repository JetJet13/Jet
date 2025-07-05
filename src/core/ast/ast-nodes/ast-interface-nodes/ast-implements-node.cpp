//
// Created by Johny Georges on 2025-07-05.
//

#include "ast-implements-node.h"

ASTNodeType ASTImplementsNode::getNodeType() {
    return AST_IMPLEMENTS_NODE;
}

std::string ASTImplementsNode::toString() {
    return "IMPLEMENTS";
}