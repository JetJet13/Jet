//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-module-access-node.h"

ASTNodeType ASTModuleAccessNode::getNodeType() {
    return AST_MODULE_ACCESS_NODE;
}

std::string ASTModuleAccessNode::toString() {
    return "MODULE_ACCESS";
}