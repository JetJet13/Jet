//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-spread-node.h"

ASTNodeType ASTModuleSpreadNode::getNodeType() {
    return AST_MODULE_SPREAD_NODE;
}

std::string ASTModuleSpreadNode::toString() {
    return "MODULE_SPREAD";
}