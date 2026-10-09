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
// Created by Johny Georges on 2024-06-04.
//

#include "ast-use-many-by-wildcard-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseManyByWildcardModuleDeclarationNode::ASTUseManyByWildcardModuleDeclarationNode(std::shared_ptr<ASTUseNode> useKeyword, std::shared_ptr<ASTImportModuleListByWildcardItemNode> importModuleListByWildcardItemNode, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path) {
    _useKeyword = useKeyword;
    _importModuleListByWildcardItemNode = importModuleListByWildcardItemNode;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_useKeyword);
    _children.push_back(_importModuleListByWildcardItemNode);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

std::shared_ptr<ASTImportModuleListByWildcardItemNode> ASTUseManyByWildcardModuleDeclarationNode::getImportModuleListByWildcardItemNode() {
    return _importModuleListByWildcardItemNode;
}

std::shared_ptr<ASTImportPathNode> ASTUseManyByWildcardModuleDeclarationNode::getPath() {
    return _path;
}

std::shared_ptr<Position> ASTUseManyByWildcardModuleDeclarationNode::getStartPosition() {
    return _useKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTUseManyByWildcardModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTUseManyByWildcardModuleDeclarationNode::getNodeType() {
    return AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE;
}

std::string ASTUseManyByWildcardModuleDeclarationNode::toString() {
    return "USE_MANY_BY_WILDCARD_MODULE_DECLARATION";
}

bool ASTUseManyByWildcardModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTUseManyByWildcardModuleDeclarationNode>(other);
    return this->getImportModuleListByWildcardItemNode()->isSameAs(otherNode->getImportModuleListByWildcardItemNode()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseManyByWildcardModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _useKeyword->print();
    _importModuleListByWildcardItemNode->print();
    _fromKeyword->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTUseManyByWildcardModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_useKeyword)
    ->add(_importModuleListByWildcardItemNode)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}