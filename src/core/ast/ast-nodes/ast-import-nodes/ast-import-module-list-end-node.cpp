//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTImportModuleListEndNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_END_NODE;
}

std::string ASTImportModuleListEndNode::toString() {
    return "IMPORT_MODULE_LIST_END";
}