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
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-constructor-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassConstructorDeclarationNode::ASTClassConstructorDeclarationNode(std::shared_ptr<ASTConstructorNode> constructor, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> content) {
    _constructor = constructor;
    _block = content;
    _parameters = parameters;
    _children.push_back(_constructor);
    _children.push_back(_block);
    _children.push_back(_parameters);
}

std::shared_ptr<ASTConstructorNode> ASTClassConstructorDeclarationNode::getConstructor() {
    return _constructor;
}

std::shared_ptr<ASTFunctionParameterListNode> ASTClassConstructorDeclarationNode::getParameters() {
    return _parameters;
}

std::shared_ptr<ASTFunctionBlockNode> ASTClassConstructorDeclarationNode::getBlock() {
    return _block;
}

uint64_t ASTClassConstructorDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

void ASTClassConstructorDeclarationNode::setTypeSignature(std::shared_ptr<ClassConstructorTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<ClassConstructorTypeSignature> ASTClassConstructorDeclarationNode::getConstructorTypeSignature() {
    return std::dynamic_pointer_cast<ClassConstructorTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTClassConstructorDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTClassConstructorDeclarationNode::getStartPosition() {
    return _constructor->getStartPosition();
}

std::shared_ptr<Position> ASTClassConstructorDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTClassConstructorDeclarationNode::getNodeType() {
    return AST_CLASS_CONSTRUCTOR_DECLARATION_NODE;
}

std::string ASTClassConstructorDeclarationNode::toString() {
    return "CLASS_CONSTRUCTOR_DECLARATION";
}

bool ASTClassConstructorDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassConstructorDeclarationNode>(other);

    return this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTClassConstructorDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameters->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTClassConstructorDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_constructor)
    ->add(_parameters)
    ->add(_block);
    return sourceCodeBuilder.build();
}
