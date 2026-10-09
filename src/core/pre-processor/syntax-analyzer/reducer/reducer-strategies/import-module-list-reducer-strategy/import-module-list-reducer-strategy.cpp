// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-module-list-node.h"

std::shared_ptr<ASTNode> ImportModuleListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto importModuleListNode = std::make_shared<ASTImportModuleListNode>(std::dynamic_pointer_cast<ASTImportModuleListStartNode>(nodes[0]), std::dynamic_pointer_cast<ASTImportModuleListEndNode>(nodes[nodes.size() - 1]));
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
                std::make_shared<ASTImportModuleListItemNode>(
                        std::dynamic_pointer_cast<ASTImportModuleListBaseItemNode>(node)
                )
            );
        }
    }
    return importModuleListNode;
}