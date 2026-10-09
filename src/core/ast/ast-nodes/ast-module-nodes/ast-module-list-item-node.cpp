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

#include "ast-module-list-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleListItemNode::ASTModuleListItemNode(std::shared_ptr<ASTModuleListBaseItemNode> item) {
    _item = item;
    _children.push_back(_item);
}

std::shared_ptr<ASTModuleListBaseItemNode> ASTModuleListItemNode::getItem() {
    return _item;
}

std::shared_ptr<Position> ASTModuleListItemNode::getStartPosition() {
    return _item->getStartPosition();
}

std::shared_ptr<Position> ASTModuleListItemNode::getEndPosition() {
    return _item->getEndPosition();
}

ASTNodeType ASTModuleListItemNode::getNodeType() {
    return AST_MODULE_LIST_ITEM_NODE;
}

std::string ASTModuleListItemNode::toString() {
    return "MODULE_LIST_ITEM";
}

bool ASTModuleListItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleListItemNode>(other);
    return _item->isSameAs(otherNode->getItem());
}

void ASTModuleListItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _item->print();
    Logger::log("----------");
}

std::string ASTModuleListItemNode::toSourceCode() {
    return _item->toSourceCode();
}