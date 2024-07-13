//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue) {
    _irValue = irValue;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

void IRBlockNode::insert(IRDeclarationNode* irNode) {
    irNode->insertSelfIntoBlock(&_builder);
}

void IRBlockNode::insert(IRStatementNode* irNode) {
    irNode->insertSelfIntoBlock(&_builder);
}