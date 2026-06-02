//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-module-access-type-node.h"

ASTNodeType ASTModuleAccessTypeNode::getNodeType() {
    return AST_MODULE_ACCESS_TYPE_NODE;
}

std::string ASTModuleAccessTypeNode::toString() {
    return "MODULE_ACCESS_TYPE";
}