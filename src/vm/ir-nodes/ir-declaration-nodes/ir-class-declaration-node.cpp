//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-declaration-node.h"

#include <utility>

IRClassDeclarationNode::IRClassDeclarationNode(ASTClassDeclarationNode* node, IRClassType* type, std::optional<IRClassPreConstructorNode*> preConstructor, std::vector<IRClassConstructorNode*> constructors, std::vector<IRClassMethodNode*> methods) {
    _node = node;
    _type = type;
    _preConstructor = preConstructor;
    _constructors = std::move(constructors);
    _methods = std::move(methods);
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

llvm::Value* IRClassDeclarationNode::getValue()  {
    throw std::logic_error("class declaration does not have a defined llvm value");
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