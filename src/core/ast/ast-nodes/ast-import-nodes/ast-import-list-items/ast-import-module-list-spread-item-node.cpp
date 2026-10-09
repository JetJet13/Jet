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

#include "ast-import-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListSpreadItemNode::ASTImportModuleListSpreadItemNode(std::shared_ptr<ASTImportSpreadNode> spread, std::shared_ptr<ASTImportModuleNameNode> moduleName) {
    _spread = spread;
    _moduleName = moduleName;
    _children.push_back(_spread);
    _children.push_back(_moduleName);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportModuleListSpreadItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<Position> ASTImportModuleListSpreadItemNode::getStartPosition() {
    return _spread->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleListSpreadItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTImportModuleListSpreadItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTImportModuleListSpreadItemNode::toString() {
    return "IMPORT_MODULE_LIST_SPREAD_ITEM";
}

bool ASTImportModuleListSpreadItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListSpreadItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTImportModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTImportModuleListSpreadItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_spread)
    ->add(_moduleName);
    return sourceCodeBuilder.build();
}