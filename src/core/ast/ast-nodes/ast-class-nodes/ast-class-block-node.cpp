//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassBlockNode::ASTClassBlockNode() {
    _properties = std::vector<ASTClassPropertyDeclarationNode*>();
    _methods = std::vector<ASTClassMethodDeclarationNode*>();
    _constructors = std::vector<ASTClassConstructorDeclarationNode*>();
}

ASTClassBlockNode::ASTClassBlockNode(std::vector<ASTNode*> nodes) {
    _properties = std::vector<ASTClassPropertyDeclarationNode*>();
    _methods = std::vector<ASTClassMethodDeclarationNode*>();
    _constructors = std::vector<ASTClassConstructorDeclarationNode*>();
    for (auto node : nodes) {
        if (node->is(AST_CLASS_PROPERTY_DECLARATION_NODE)) {
            this->addProperty((ASTClassPropertyDeclarationNode*)node);
        }
        if (node->is(AST_CLASS_METHOD_DECLARATION_NODE)) {
            this->addMethod((ASTClassMethodDeclarationNode*)node);
        }
        if (node->is(AST_CLASS_CONSTRUCTOR_DECLARATION_NODE)) {
            this->addConstructor((ASTClassConstructorDeclarationNode*)node);
        }
    }
}

ASTClassBlockNode::ASTClassBlockNode(std::vector<ASTClassPropertyDeclarationNode*> properties, std::vector<ASTClassMethodDeclarationNode*> methods, std::vector<ASTClassConstructorDeclarationNode*> constructors) {
    _properties = std::vector<ASTClassPropertyDeclarationNode*>();
    for (auto property: properties) {
        _properties.push_back(property);
    }

    _methods = std::vector<ASTClassMethodDeclarationNode*>();
    for (auto method: methods) {
        _methods.push_back(method);
    }

    _constructors = std::vector<ASTClassConstructorDeclarationNode*>();
    for (auto constructor: constructors) {
        _constructors.push_back(constructor);
    }
}
void ASTClassBlockNode::addProperty(ASTClassPropertyDeclarationNode* property) {
    _properties.push_back(property);
}

void ASTClassBlockNode::addMethod(ASTClassMethodDeclarationNode* method) {
    _methods.push_back(method);
}

void ASTClassBlockNode::addConstructor(ASTClassConstructorDeclarationNode* constructor) {
    _constructors.push_back(constructor);
}

std::vector<ASTClassPropertyDeclarationNode*>* ASTClassBlockNode::getProperties() {
    return &_properties;
}

std::vector<ASTClassMethodDeclarationNode*>* ASTClassBlockNode::getMethods() {
    return &_methods;
}

std::vector<ASTClassConstructorDeclarationNode*>* ASTClassBlockNode::getConstructors() {
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
    for (auto method : _methods) {
        method->print();
    }
    for (auto constructor : _constructors) {
        constructor->print();
    }
    Logger::log("----------");
}