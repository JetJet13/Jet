//
// Created by Johny Georges on 2024-04-13.
//

#include "module-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-list-node.h"

ASTNode* ModuleListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto moduleListNode = new ASTModuleListNode((ASTModuleListStartNode*)nodes[0], (ASTModuleListEndNode*)nodes[nodes.size() - 1]);
    for (auto node : nodes) {
        if (node->isOneOf({AST_MODULE_LIST_NORMAL_ITEM_NODE, AST_MODULE_LIST_SPREAD_ITEM_NODE, AST_MODULE_LIST_ALIAS_ITEM_NODE })) {
            moduleListNode->addItem(
                    new ASTModuleListItemNode((ASTModuleListBaseItemNode*)node)
            );
        }
    }
    return moduleListNode;
}