//
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-module-list-node.h"

ASTNode* ImportModuleListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto importModuleListNode = new ASTImportModuleListNode();
    for (auto node : nodes) {
        if (node->isOneOf({
            AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE,
            AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE,
            AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE,
            AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE,
            AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE,
            AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE
            })) {
            importModuleListNode->addItem(
                new ASTImportModuleListItemNode(
                        (ASTImportModuleListBaseItemNode*)node
                )
            );
        }
    }
    return importModuleListNode;
}