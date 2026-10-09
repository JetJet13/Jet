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
// Created by Johny Georges on 2024-04-15.
//

#include "ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListByWildcardItemNode::ASTImportModuleListByWildcardItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTModuleAccessNode> moduleAccessNode, std::shared_ptr<ASTImportWildcardNode> wildcard) {
    _moduleName = moduleName;
    _moduleAccessNode = moduleAccessNode;
    _wildcard = wildcard;
    _children.push_back(_moduleName);
    _children.push_back(_moduleAccessNode);
    _children.push_back(_wildcard);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportModuleListByWildcardItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<ASTImportWildcardNode> ASTImportModuleListByWildcardItemNode::getWildcard() {
    return _wildcard;
}

std::shared_ptr<Position> ASTImportModuleListByWildcardItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleListByWildcardItemNode::getEndPosition() {
    return _wildcard->getEndPosition();
}

ASTNodeType ASTImportModuleListByWildcardItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE;
}

std::string ASTImportModuleListByWildcardItemNode::toString() {
    return "IMPORT_MODULE_LIST_BY_WILDCARD_ITEM";
}

bool ASTImportModuleListByWildcardItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListByWildcardItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
           this->getWildcard()->isSameAs(otherNode->getWildcard());
}

void ASTImportModuleListByWildcardItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _moduleAccessNode->print();
    _wildcard->print();
    Logger::log("----------");
}

std::string ASTImportModuleListByWildcardItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_moduleAccessNode)
    ->add(_wildcard);
    return sourceCodeBuilder.build();
}