//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-module-type-target-node.h"

ASTNodeType ASTModuleTypeTargetNode::getNodeType() {
    return AST_MODULE_TYPE_TARGET_NODE;
}

std::string ASTModuleTypeTargetNode::toString() {
    return "MODULE_TYPE_TARGET";
}