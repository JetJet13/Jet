//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTImportModuleListStartNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_START_NODE;
}

std::string ASTImportModuleListStartNode::toString() {
    return "IMPORT_MODULE_LIST_START";
}