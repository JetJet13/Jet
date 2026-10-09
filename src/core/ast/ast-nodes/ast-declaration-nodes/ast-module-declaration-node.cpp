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

#include "ast-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleDeclarationNode::ASTModuleDeclarationNode(std::shared_ptr<ASTModuleNode> moduleKeyword, std::shared_ptr<ASTModuleNameNode> name) {
    _moduleKeyword = moduleKeyword;
    _name = name;
    _children.push_back(_name);
}


std::shared_ptr<ASTModuleNameNode> ASTModuleDeclarationNode::getName() {
    return _name;
}

std::vector<std::shared_ptr<ASTNode>>* ASTModuleDeclarationNode::getExports() {
    return &_exportedDeclarations;
}

void ASTModuleDeclarationNode::addExportedDeclaration(std::shared_ptr<ASTNode> declarationNode) {
    _exportedDeclarations.push_back(declarationNode);
}

void ASTModuleDeclarationNode::setTypeSignature(std::shared_ptr<ModuleTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<ModuleTypeSignature> ASTModuleDeclarationNode::getModuleTypeSignature() {
    return std::dynamic_pointer_cast<ModuleTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTModuleDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTModuleDeclarationNode::getStartPosition() {
    return _moduleKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTModuleDeclarationNode::getEndPosition() {
    return _moduleKeyword->getEndPosition();
}

ASTNodeType ASTModuleDeclarationNode::getNodeType() {
    return AST_MODULE_DECLARATION_NODE;
}

std::string ASTModuleDeclarationNode::toString() {
    return "MODULE_DECLARATION";
}

bool ASTModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleDeclarationNode>(other);

    return  this->getName()->isSameAs(otherNode->getName());
}

void ASTModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    Logger::log("----------");
}

std::string ASTModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleKeyword)
    ->add(_name);
    return sourceCodeBuilder.build();
}