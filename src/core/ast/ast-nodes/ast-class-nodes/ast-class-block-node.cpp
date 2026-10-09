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
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassBlockNode::ASTClassBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> nodes, std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _properties = std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>();
    _instanceProperties = std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>();
    _staticProperties = std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>();
    _methods = std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>();
    _staticMethods = std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>();
    _instanceMethods = std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>();
    _constructors = std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>>();
    for (auto node : nodes) {
        if (node->is(AST_CLASS_PROPERTY_DECLARATION_NODE)) {
            this->addProperty(std::dynamic_pointer_cast<ASTClassPropertyDeclarationNode>(node));
        }
        if (node->is(AST_CLASS_METHOD_DECLARATION_NODE)) {
            this->addMethod(std::dynamic_pointer_cast<ASTClassMethodDeclarationNode>(node));
        }
        if (node->is(AST_CLASS_CONSTRUCTOR_DECLARATION_NODE)) {
            this->addConstructor(std::dynamic_pointer_cast<ASTClassConstructorDeclarationNode>(node));
        }
    }
}

ASTClassBlockNode::ASTClassBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>> properties, std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>> methods, std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>> constructors, std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;

    _instanceProperties = std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>();
    _staticProperties = std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>();
    for (auto property: properties) {
        this->addProperty(property);
    }

    _methods = std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>();
    for (auto method: methods) {
        this->addMethod(method);
    }

    _constructors = std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>>();
    for (auto constructor: constructors) {
        this->addConstructor(constructor);
    }
}
void ASTClassBlockNode::addProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> property) {
    _properties.push_back(property);
    if (property->isStatic()) {
        _staticProperties.push_back(property);
    } else {
        _instanceProperties.push_back(property);
    }
    _children.push_back(property);
}

void ASTClassBlockNode::addMethod(std::shared_ptr<ASTClassMethodDeclarationNode> method) {
    _methods.push_back(method);
    if (method->isStatic()) {
        _staticMethods.push_back(method);
    } else {
        _instanceMethods.push_back(method);
    }
    _children.push_back(method);
}

void ASTClassBlockNode::addConstructor(std::shared_ptr<ASTClassConstructorDeclarationNode> constructor) {
    _constructors.push_back(constructor);
    _children.push_back(constructor);
}

std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* ASTClassBlockNode::getProperties() {
    return &_properties;
}

std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* ASTClassBlockNode::getStaticProperties() {
    return &_staticProperties;
}

std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* ASTClassBlockNode::getInstanceProperties() {
    return &_instanceProperties;
}

std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>* ASTClassBlockNode::getMethods() {
    return &_methods;
}

std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>* ASTClassBlockNode::getStaticMethods() {
    return &_staticMethods;
}

std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>>* ASTClassBlockNode::getInstanceMethods() {
    return &_instanceMethods;
}

std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>>* ASTClassBlockNode::getConstructors() {
    return &_constructors;
}

std::shared_ptr<Position> ASTClassBlockNode::getStartPosition() {
    return _blockStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTClassBlockNode::getEndPosition() {
    return _blockEndNode->getEndPosition();
}

ASTNodeType ASTClassBlockNode::getNodeType() {
    return AST_CLASS_BLOCK_NODE;
}

std::string ASTClassBlockNode::toString() {
    return "CLASS_BLOCK";
}

bool ASTClassBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassBlockNode>(other);
    for (uint64_t i = 0; i < _instanceProperties.size(); ++i) {
        if (!_instanceProperties[i]->isSameAs(otherNode->getInstanceProperties()->at(i))) {
            return false;
        }
    }

    for (uint64_t i = 0; i < _staticProperties.size(); ++i) {
        if (!_staticProperties[i]->isSameAs(otherNode->getStaticProperties()->at(i))) {
            return false;
        }
    }

    for (uint64_t i = 0; i < _methods.size(); ++i) {
        if (!_methods[i]->isSameAs(otherNode->getMethods()->at(i))) {
            return false;
        }
    }

    for (uint64_t i = 0; i < _staticMethods.size(); ++i) {
        if (!_staticMethods[i]->isSameAs(otherNode->getStaticMethods()->at(i))) {
            return false;
        }
    }

    for (uint64_t i = 0; i < _constructors.size(); ++i) {
        if (!_constructors[i]->isSameAs(otherNode->getConstructors()->at(i))) {
            return false;
        }
    }
    return true;
}

void ASTClassBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto property : _properties) {
        property->print();
    }
    for (auto method : _methods) {
        method->print();
    }
    for (auto constructor : _constructors) {
        constructor->print();
    }
    Logger::log("----------");
}

std::string ASTClassBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_blockStartNode);
    for (auto property : _properties) {
        sourceCodeBuilder.add(property);
    }
    for (auto constructor : _constructors) {
        sourceCodeBuilder.add(constructor);
    }
    for (auto method : _methods) {
        sourceCodeBuilder.add(method);
    }
    sourceCodeBuilder.add(_blockEndNode);
    return sourceCodeBuilder.build();
}