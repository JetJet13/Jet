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

#include "ast-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTModuleListSpreadItemNode::ASTModuleListSpreadItemNode(std::shared_ptr<ASTModuleNameNode> moduleName, std::shared_ptr<ASTModuleSpreadNode> spread) {
    _moduleName = moduleName;
    _spread = spread;
    _children.push_back(_moduleName);
    _children.push_back(_spread);
}

std::shared_ptr<ASTModuleNameNode> ASTModuleListSpreadItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<Position> ASTModuleListSpreadItemNode::getStartPosition() {
    return _spread->getStartPosition();
}

std::shared_ptr<Position> ASTModuleListSpreadItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTModuleListSpreadItemNode::getNodeType() {
    return AST_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTModuleListSpreadItemNode::toString() {
    return "MODULE_LIST_SPREAD_ITEM";
}

bool ASTModuleListSpreadItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleListSpreadItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTModuleListSpreadItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_spread);
    return sourceCodeBuilder.build();
}