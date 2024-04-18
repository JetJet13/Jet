//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-protected-node.h"

ASTNodeType ASTProtectedNode::getNodeType() {
    return AST_PROTECTED_NODE;
}

std::string ASTProtectedNode::toString() {
    return "PROTECTED";
}