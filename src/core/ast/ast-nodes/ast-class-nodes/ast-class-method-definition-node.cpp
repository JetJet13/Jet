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
// Created by Johny Georges on 2024-04-26.
//

#include "ast-class-method-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassMethodDefinitionNode::ASTClassMethodDefinitionNode(std::shared_ptr<ASTAccessModifierNode> accessModifier, std::shared_ptr<ASTClassMethodNameNode> methodName, std::optional<std::shared_ptr<ASTStaticNode>> staticKeyword) {
    _accessModifier = accessModifier;
    _methodName = methodName;
    _staticKeyword = staticKeyword;
    _children.push_back(_accessModifier);
    _children.push_back(_methodName);
    if (_staticKeyword) {
        _children.push_back(_staticKeyword.value());
    }
}

std::shared_ptr<ASTAccessModifierNode> ASTClassMethodDefinitionNode::getAccessModifier() {
    return _accessModifier;
}

std::shared_ptr<ASTClassMethodNameNode> ASTClassMethodDefinitionNode::getMethodName() {
    return _methodName;
}

bool ASTClassMethodDefinitionNode::isStatic() {
    return _staticKeyword.has_value();
}

std::shared_ptr<Position> ASTClassMethodDefinitionNode::getStartPosition() {
    return _accessModifier->getStartPosition();
}

std::shared_ptr<Position> ASTClassMethodDefinitionNode::getEndPosition() {
    return _methodName->getEndPosition();
}

ASTNodeType ASTClassMethodDefinitionNode::getNodeType() {
    return AST_CLASS_METHOD_DEFINITION_NODE;
}

std::string ASTClassMethodDefinitionNode::toString() {
    return "CLASS_METHOD_DEFINITION";
}

bool ASTClassMethodDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTClassMethodDefinitionNode>(other);
    return this->getAccessModifier()->isSameAs(otherNode->getAccessModifier()) &&
           this->getMethodName()->isSameAs(otherNode->getMethodName()) &&
           this->isStatic() == otherNode->isStatic();
}

void ASTClassMethodDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _accessModifier->print();
    _methodName->print();
    Logger::log("isStatic -", this->isStatic());
    Logger::log("----------");
}

std::string ASTClassMethodDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_accessModifier);
    if (_staticKeyword) {
        sourceCodeBuilder.add(_staticKeyword.value());
    }
    sourceCodeBuilder.add(_methodName);
    return sourceCodeBuilder.build();
}