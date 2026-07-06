//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-declaration-node.h"

#include <utility>

IRClassDeclarationNode::IRClassDeclarationNode(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRClassType> type, std::optional<std::shared_ptr<IRClassPreConstructorNode>> preConstructor, std::vector<std::shared_ptr<IRClassConstructorNode>> constructors, std::vector<std::shared_ptr<IRClassMethodNode>> methods, std::vector<std::shared_ptr<IRClassMethodNode>> staticMethods, std::vector<std::shared_ptr<IRClassStaticPropertyNode>> staticProperties) {
    _node = node;
    _type = type;
    _irValue = irValue;
    _preConstructor = preConstructor;
    _constructors = std::move(constructors);
    _methods = std::move(methods);
    _staticMethods = std::move(staticMethods);
    _staticProperties = std::move(staticProperties);
}

std::shared_ptr<IRClassType> IRClassDeclarationNode::getIRType() {
    return _type;
}

std::optional<std::shared_ptr<IRClassPreConstructorNode>> IRClassDeclarationNode::getPreConstructor() {
    return _preConstructor;
}

std::vector<std::shared_ptr<IRClassConstructorNode>>* IRClassDeclarationNode::getConstructors() {
    return &_constructors;
}

std::vector<std::shared_ptr<IRClassMethodNode>>* IRClassDeclarationNode::getMethods() {
    return &_methods;
}

std::vector<std::shared_ptr<IRClassMethodNode>>* IRClassDeclarationNode::getStaticMethods() {
    return &_staticMethods;
}

std::vector<std::shared_ptr<IRClassStaticPropertyNode>>* IRClassDeclarationNode::getStaticProperties() {
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