//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-module-type-source-node.h"

ASTNodeType ASTModuleTypeSourceNode::getNodeType() {
    return AST_MODULE_TYPE_SOURCE_NODE;
}

std::string ASTModuleTypeSourceNode::toString() {
    return "MODULE_TYPE_SOURCE";
}