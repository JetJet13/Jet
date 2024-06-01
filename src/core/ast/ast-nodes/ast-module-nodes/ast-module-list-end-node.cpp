//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTModuleListEndNode::getNodeType() {
    return AST_MODULE_LIST_END_NODE;
}

std::string ASTModuleListEndNode::toString() {
    return "MODULE_LIST_END";
}
