//
// Created by Johny Georges on 2024-04-13.
//

#include "module-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-list-node.h"

std::shared_ptr<ASTNode> ModuleListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto moduleListNode = std::make_shared<ASTModuleListNode>(std::dynamic_pointer_cast<ASTModuleListStartNode>(nodes[0]), std::dynamic_pointer_cast<ASTModuleListEndNode>(nodes[nodes.size() - 1]));
    for (auto node : nodes) {
        if (node->isOneOf({AST_MODULE_LIST_NORMAL_ITEM_NODE, AST_MODULE_LIST_SPREAD_ITEM_NODE, AST_MODULE_LIST_ALIAS_ITEM_NODE })) {
            moduleListNode->addItem(
                    std::make_shared<ASTModuleListItemNode>(std::dynamic_pointer_cast<ASTModuleListBaseItemNode>(node))
            );
        }
    }
    return moduleListNode;
}