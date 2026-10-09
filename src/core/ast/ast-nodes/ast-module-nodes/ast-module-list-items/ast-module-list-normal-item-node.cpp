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

#include "ast-module-list-normal-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTModuleListNormalItemNode::ASTModuleListNormalItemNode(std::shared_ptr<ASTModuleNameNode> moduleName) {
    _moduleName = moduleName;
    _children.push_back(_moduleName);
}

std::shared_ptr<ASTModuleNameNode> ASTModuleListNormalItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<Position> ASTModuleListNormalItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

std::shared_ptr<Position> ASTModuleListNormalItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTModuleListNormalItemNode::getNodeType() {
    return AST_MODULE_LIST_NORMAL_ITEM_NODE;
}

std::string ASTModuleListNormalItemNode::toString() {
    return "MODULE_LIST_NORMAL_ITEM";
}

bool ASTModuleListNormalItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleListNormalItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTModuleListNormalItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTModuleListNormalItemNode::toSourceCode() {
    return _moduleName->toSourceCode();
}