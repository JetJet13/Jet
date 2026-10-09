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
// Created by Johny Georges on 2024-04-22.
//

#include "ast-class-property-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassPropertyDefinitionNode::ASTClassPropertyDefinitionNode(std::shared_ptr<ASTAccessModifierNode> accessModifier, std::shared_ptr<ASTClassPropertyNameNode> propertyName, std::optional<std::shared_ptr<ASTStaticNode>> staticKeyword, std::optional<std::shared_ptr<ASTConstNode>> constKeyword) {
    _accessModifier = accessModifier;
    _propertyName = propertyName;
    _staticKeyword = staticKeyword;
    _constKeyword = constKeyword;
    _children.push_back(_accessModifier);
    if (_staticKeyword){
        _children.push_back(_staticKeyword.value());
    }
    if (_constKeyword){
        _children.push_back(_constKeyword.value());
    }
    _children.push_back(_propertyName);
}

std::shared_ptr<ASTAccessModifierNode> ASTClassPropertyDefinitionNode::getAccessModifier() {
    return _accessModifier;
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertyDefinitionNode::getPropertyName() {
    return _propertyName;
}

std::optional<std::shared_ptr<ASTStaticNode>> ASTClassPropertyDefinitionNode::getStatic() {
    return _staticKeyword;
}

std::optional<std::shared_ptr<ASTConstNode>> ASTClassPropertyDefinitionNode::getConstant() {
    return _constKeyword;
}

bool ASTClassPropertyDefinitionNode::isStatic() {
    return _staticKeyword.has_value();
}

bool ASTClassPropertyDefinitionNode::isConstant() {
    return _constKeyword.has_value();
}

std::shared_ptr<Position> ASTClassPropertyDefinitionNode::getStartPosition() {
    return _accessModifier->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertyDefinitionNode::getEndPosition() {
    return _propertyName->getEndPosition();
}

ASTNodeType ASTClassPropertyDefinitionNode::getNodeType() {
    return AST_CLASS_PROPERTY_DEFINITION_NODE;
}

std::string ASTClassPropertyDefinitionNode::toString() {
    return "CLASS_PROPERTY_DEFINITION";
}

bool ASTClassPropertyDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyDefinitionNode>(other);

    return this->getAccessModifier()->isSameAs(otherNode->getAccessModifier()) &&
           this->getPropertyName()->isSameAs(otherNode->getPropertyName()) &&
           this->isStatic() == otherNode->isStatic() &&
           this->isConstant() == otherNode->isConstant();
}

void ASTClassPropertyDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _accessModifier->print();
    _propertyName->print();
    Logger::log("isStatic -", this->isStatic());
    Logger::log("isConstant -", this->isConstant());
    Logger::log("----------");
}

std::string ASTClassPropertyDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_accessModifier);
    if (_staticKeyword){
        sourceCodeBuilder.add(_staticKeyword.value());
    }
    if (_constKeyword){
        sourceCodeBuilder.add(_constKeyword.value());
    }
    sourceCodeBuilder.add(_propertyName);
    return sourceCodeBuilder.build();
}