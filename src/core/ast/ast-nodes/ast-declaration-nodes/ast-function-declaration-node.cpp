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
// Created by Johny Georges on 2024-03-18.
//

#include "ast-function-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionDeclarationNode::ASTFunctionDeclarationNode(std::shared_ptr<ASTFunctionDefinitionNode> functionDefinition, std::shared_ptr<ASTFunctionBlockNode> content, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword) {
    _functionDefinition = functionDefinition;
    _block = content;
    _exportKeyword = exportKeyword;
    _children.push_back(_functionDefinition);
    _children.push_back(_block);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }
}

std::shared_ptr<ASTFunctionParameterListNode> ASTFunctionDeclarationNode::getParameters() {
    return _functionDefinition->getParameters();
}

std::shared_ptr<ASTFunctionNameNode> ASTFunctionDeclarationNode::getName() {
    return _functionDefinition->getName();
}

std::shared_ptr<ASTTypeNode> ASTFunctionDeclarationNode::getReturnType() {
    return _functionDefinition->getReturnType();
}

std::shared_ptr<ASTFunctionBlockNode> ASTFunctionDeclarationNode::getBlock() {
    return _block;
}

std::shared_ptr<ASTFunctionDefinitionNode> ASTFunctionDeclarationNode::getDefinition() {
    return _functionDefinition;
}

uint64_t ASTFunctionDeclarationNode::numParameters() {
    return _functionDefinition->numParameters();
}

bool ASTFunctionDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

void ASTFunctionDeclarationNode::setTypeSignature(std::shared_ptr<FunctionTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<FunctionTypeSignature> ASTFunctionDeclarationNode::getFunctionTypeSignature() {
    return std::dynamic_pointer_cast<FunctionTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTFunctionDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTFunctionDeclarationNode::getStartPosition() {
    return _functionDefinition->getStartPosition();
}

std::shared_ptr<Position> ASTFunctionDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTFunctionDeclarationNode::getNodeType() {
    return AST_FUNCTION_DECLARATION_NODE;
}

std::string ASTFunctionDeclarationNode::toString() {
    return "FUNCTION_DECLARATION";
}

bool ASTFunctionDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(other);

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getReturnType()->isSameAs(otherNode->getReturnType()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTFunctionDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_exportKeyword) {
        _exportKeyword.value()->print();
    }
    _functionDefinition->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTFunctionDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    if (_exportKeyword) {
        sourceCodeBuilder.add(_exportKeyword.value())->add(_functionDefinition);
    } else {
        sourceCodeBuilder.add(_functionDefinition);
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}