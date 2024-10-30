//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-node.h"

ASTNodeType ASTModuleNode::getNodeType() {
    return AST_MODULE_NODE;
}

std::string ASTModuleNode::toString() {
    return "MODULE";
}