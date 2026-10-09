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
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseManyModuleDeclarationNode::ASTUseManyModuleDeclarationNode(std::shared_ptr<ASTUseNode> useKeyword, std::shared_ptr<ASTImportModuleListByGroupItemNode> importModuleListByGroupItem, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path) {
    _useKeyword = useKeyword;
    _importModuleListByGroupItem = importModuleListByGroupItem;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_useKeyword);
    _children.push_back(_importModuleListByGroupItem);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

std::shared_ptr<ASTImportModuleListByGroupItemNode> ASTUseManyModuleDeclarationNode::getImportModuleListByGroupItem() {
    return _importModuleListByGroupItem;
}

std::shared_ptr<ASTImportModuleNameNode> ASTUseManyModuleDeclarationNode::getModuleName() {
    return _importModuleListByGroupItem->getModuleName();
}

std::shared_ptr<ASTImportModuleListNode> ASTUseManyModuleDeclarationNode::getModuleList() {
    return _importModuleListByGroupItem->getModuleList();
}

std::shared_ptr<ASTImportPathNode> ASTUseManyModuleDeclarationNode::getPath() {
    return _path;
}

std::shared_ptr<Position> ASTUseManyModuleDeclarationNode::getStartPosition() {
    return _useKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTUseManyModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTUseManyModuleDeclarationNode::getNodeType() {
    return AST_USE_MANY_MODULE_DECLARATION_NODE;
}

std::string ASTUseManyModuleDeclarationNode::toString() {
    return "USE_MANY_MODULE_DECLARATION";
}

bool ASTUseManyModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTUseManyModuleDeclarationNode>(other);
    return this->getImportModuleListByGroupItem()->isSameAs(otherNode->getImportModuleListByGroupItem()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseManyModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importModuleListByGroupItem->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTUseManyModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_useKeyword)
    ->add(_importModuleListByGroupItem)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}