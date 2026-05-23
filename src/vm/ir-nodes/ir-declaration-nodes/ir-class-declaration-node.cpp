//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-declaration-node.h"

#include <utility>

IRClassDeclarationNode::IRClassDeclarationNode(ASTClassDeclarationNode* node, IRInstructionNode* irValue, IRClassType* type, std::optional<IRClassPreConstructorNode*> preConstructor, std::vector<IRClassConstructorNode*> constructors, std::vector<IRClassMethodNode*> methods, std::vector<IRClassMethodNode*> staticMethods, std::vector<IRClassStaticPropertyNode*> staticProperties) {
    _node = node;
    _type = type;
    _irValue = irValue;
    _preConstructor = preConstructor;
    _constructors = std::move(constructors);
    _methods = std::move(methods);
    _staticMethods = std::move(staticMethods);
    _staticProperties = std::move(staticProperties);
}

IRClassType* IRClassDeclarationNode::getIRType() {
    return _type;
}

std::optional<IRClassPreConstructorNode*> IRClassDeclarationNode::getPreConstructor() {
    return _preConstructor;
}

std::vector<IRClassConstructorNode*>* IRClassDeclarationNode::getConstructors() {
    return &_constructors;
}

std::vector<IRClassMethodNode*>* IRClassDeclarationNode::getMethods() {
    return &_methods;
}

std::vector<IRClassMethodNode*>* IRClassDeclarationNode::getStaticMethods() {
    return &_staticMethods;
}

std::vector<IRClassStaticPropertyNode*>* IRClassDeclarationNode::getStaticProperties() {
    return &_staticProperties;
}

llvm::Value* IRClassDeclarationNode::getValue()  {
    return _irValue->getValue();
}

IRNodeType IRClassDeclarationNode::getNodeType() {
    return IR_CLASS_DECLARATION_NODE;
}

std::string IRClassDeclarationNode::toString() {
    return "IR_CLASS_DECLARATION_NODE";
}

void IRClassDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto constructor : _constructors) {
        constructor->getFunction()->print(**stream);
    }
    for (auto method : _methods) {
        method->getFunction()->print(**stream);
    }
}