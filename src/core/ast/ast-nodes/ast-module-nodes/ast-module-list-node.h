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
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_LIST_NODE_H
#define JETLANG_AST_MODULE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-module-list-item-node.h"
#include "ast-module-list-start-node.h"
#include "ast-module-list-end-node.h"

class ASTModuleListNode : public ASTNode {
private:
    std::shared_ptr<ASTModuleListStartNode> _moduleListStartNode;
    std::shared_ptr<ASTModuleListEndNode> _moduleListEndNode;
    std::vector<std::shared_ptr<ASTModuleListItemNode>> _items;
public:
    ASTModuleListNode(std::shared_ptr<ASTModuleListStartNode> moduleListStartNode, std::shared_ptr<ASTModuleListEndNode> moduleListEndNode);
    ASTModuleListNode(std::shared_ptr<ASTModuleListStartNode> moduleListStartNode, std::vector<std::shared_ptr<ASTModuleListItemNode>> items, std::shared_ptr<ASTModuleListEndNode> moduleListEndNode);
    std::vector<std::shared_ptr<ASTModuleListItemNode>> getItems();
    uint64_t numItems();
    std::shared_ptr<ASTModuleListNode> addItem(std::shared_ptr<ASTModuleListItemNode> item);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_LIST_NODE_H
