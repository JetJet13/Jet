//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassBlockNode::ASTClassBlockNode() {
    _properties = std::vector<ASTClassPropertyNode*>();
    _methods = std::vector<ASTClassMethodNode*>();
    _constructors = std::vector<ASTClassConstructorNode*>();
}

ASTClassBlockNode::ASTClassBlockNode(std::vector<ASTClassPropertyNode*> properties, std::vector<ASTClassMethodNode*> methods, std::vector<ASTClassConstructorNode*> constructors) {
    _properties = std::vector<ASTClassPropertyNode*>();
    for (auto property: properties) {
        _properties.push_back(property);
    }

    _methods = std::vector<ASTClassMethodNode*>();
    for (auto method: methods) {
        _methods.push_back(method);
    }

    _constructors = std::vector<ASTClassConstructorNode*>();
    for (auto constructor: constructors) {
        _constructors.push_back(constructor);
    }
}
void ASTClassBlockNode::addProperty(ASTClassPropertyNode* property) {
    _properties.push_back(property);
}

void ASTClassBlockNode::addMethod(ASTClassMethodNode* method) {
    _methods.push_back(method);
}

void ASTClassBlockNode::addConstructor(ASTClassConstructorNode* constructor) {
    _constructors.push_back(constructor);
}

std::vector<ASTClassPropertyNode*>* ASTClassBlockNode::getProperties() {
    return &_properties;
}

std::vector<ASTClassMethodNode*>* ASTClassBlockNode::getMethods() {
    return &_methods;
}

std::vector<ASTClassConstructorNode*>* ASTClassBlockNode::getConstructors() {
    return &_constructors;
}

ASTNodeType ASTClassBlockNode::getNodeType() {
    return AST_CLASS_BLOCK_NODE;
}

std::string ASTClassBlockNode::toString() {
    return "CLASS_BLOCK";
}

bool ASTClassBlockNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassBlockNode*)other;
    for (int i = 0; i < _properties.size(); ++i) {
        if (!_properties[i]->isSameAs(otherNode->getProperties()->at(i))) {
            return false;
        }
    }

    for (int i = 0; i < _methods.size(); ++i) {
        if (!_methods[i]->isSameAs(otherNode->getMethods()->at(i))) {
            return false;
        }
    }

    for (int i = 0; i < _constructors.size(); ++i) {
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
    for (auto constructor : _constructors) {
        constructor->print();
    }
    for (auto method : _methods) {
        method->print();
    }
    Logger::log("----------");
}