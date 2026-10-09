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

#include "ast-import-module-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListNode::ASTImportModuleListNode(std::shared_ptr<ASTImportModuleListStartNode> importModuleListStartNode, std::shared_ptr<ASTImportModuleListEndNode> importModuleListEndNode) {
    _importModuleListStartNode = importModuleListStartNode;
    _importModuleListEndNode = importModuleListEndNode;
    _children.push_back(_importModuleListStartNode);
    _children.push_back(_importModuleListEndNode);
    _items = std::vector<std::shared_ptr<ASTImportModuleListItemNode>>();
}

ASTImportModuleListNode::ASTImportModuleListNode(std::shared_ptr<ASTImportModuleListStartNode> importModuleListStartNode, std::vector<std::shared_ptr<ASTImportModuleListItemNode>> items, std::shared_ptr<ASTImportModuleListEndNode> importModuleListEndNode) {
    _importModuleListStartNode = importModuleListStartNode;
    _importModuleListEndNode = importModuleListEndNode;
    _children.push_back(_importModuleListStartNode);
    _children.push_back(_importModuleListEndNode);
    _items = std::vector<std::shared_ptr<ASTImportModuleListItemNode>>();
    for (auto item: items) {
        _items.push_back(item);
        _children.push_back(item);
    }
}

std::vector<std::shared_ptr<ASTImportModuleListItemNode>> ASTImportModuleListNode::getItems() {
    return _items;
}

uint64_t ASTImportModuleListNode::numItems() {
    return _items.size();
}

std::shared_ptr<ASTImportModuleListNode> ASTImportModuleListNode::addItem(std::shared_ptr<ASTImportModuleListItemNode> item) {
    _items.push_back(item);
    _children.push_back(item);
    return std::dynamic_pointer_cast<ASTImportModuleListNode>(shared_from_this());
}

std::shared_ptr<Position> ASTImportModuleListNode::getStartPosition() {
    return _importModuleListStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleListNode::getEndPosition() {
    return _importModuleListEndNode->getEndPosition();
}

ASTNodeType ASTImportModuleListNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_NODE;
}

std::string ASTImportModuleListNode::toString() {
    return "IMPORT_MODULE_LIST";
}

bool ASTImportModuleListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListNode>(other);
    auto otherNodeElements = otherNode->getItems();
    if (this->numItems() != otherNode->numItems()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numItems(); i++) {
        if (!_items[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTImportModuleListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto item : _items) {
        item->print();
    }
    Logger::log("----------");
}

std::string ASTImportModuleListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_importModuleListStartNode);
    for (auto item : _items) {
        sourceCodeBuilder.add(item);
    }
    sourceCodeBuilder.add(_importModuleListEndNode);
    return sourceCodeBuilder.build();
}