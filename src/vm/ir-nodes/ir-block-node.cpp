//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue) {
    _irValue = irValue;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
    _variablesToFree = std::vector<IRVariableDeclarationNode*>();
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

std::vector<IRNode*>* IRBlockNode::getBody() {
    return &_body;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getVariablesToFree() {
    return &_variablesToFree;
}

void IRBlockNode::insert(IRNode* irNode) {
    _body.push_back(irNode);
    if (irNode->is(IR_VARIABLE_DECLARATION_NODE) && ((IRVariableDeclarationNode*)irNode)->requiresFreeing()) {
        _variablesToFree.push_back((IRVariableDeclarationNode*)irNode);
    }
}

std::unique_ptr<llvm::IRBuilder<>>* IRBlockNode::getBuilder() {
    return &_builder;
}

void IRBlockNode::addVoidReturn() {
    _builder.get()->CreateRet(_builder.get()->getInt32(0));
}