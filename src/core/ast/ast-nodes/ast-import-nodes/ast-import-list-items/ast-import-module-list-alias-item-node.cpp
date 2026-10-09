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

#include "ast-import-module-list-alias-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListAliasItemNode::ASTImportModuleListAliasItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTAsNode> asKeyword, std::shared_ptr<ASTImportModuleAliasNameNode> aliasModuleName) {
    _moduleName = moduleName;
    _asKeyword = asKeyword;
    _aliasModuleName = aliasModuleName;
    _children.push_back(_moduleName);
    _children.push_back(_asKeyword);
    _children.push_back(_aliasModuleName);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportModuleListAliasItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<ASTImportModuleAliasNameNode> ASTImportModuleListAliasItemNode::getAliasModuleName() {
    return _aliasModuleName;
}

std::shared_ptr<Position> ASTImportModuleListAliasItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleListAliasItemNode::getEndPosition() {
    return _aliasModuleName->getEndPosition();
}

ASTNodeType ASTImportModuleListAliasItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE;
}

std::string ASTImportModuleListAliasItemNode::toString() {
    return "IMPORT_MODULE_LIST_ALIAS_ITEM";
}

bool ASTImportModuleListAliasItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListAliasItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getAliasModuleName()->isSameAs(otherNode->getAliasModuleName()) ;
}

void ASTImportModuleListAliasItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _aliasModuleName->print();
    Logger::log("----------");
}

std::string ASTImportModuleListAliasItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_asKeyword)
    ->add(_aliasModuleName);
    return sourceCodeBuilder.build();
}