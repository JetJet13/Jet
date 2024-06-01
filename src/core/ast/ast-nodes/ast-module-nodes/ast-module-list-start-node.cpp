//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTModuleListStartNode::getNodeType() {
    return AST_MODULE_LIST_START_NODE;
}

std::string ASTModuleListStartNode::toString() {
    return "MODULE_LIST_START";
}