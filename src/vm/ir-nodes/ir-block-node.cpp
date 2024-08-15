//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue, IRInjectorMap* injectorMap) {
    _irValue = irValue;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
    _injectorMap = injectorMap;
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

void IRBlockNode::inject(IRDeclarationNode* irNode) {
    irNode->insertSelfIntoBlock(&_builder, _injectorMap);
}

void IRBlockNode::inject(IRStatementNode* irNode) {
    irNode->insertSelfIntoBlock(&_builder, _injectorMap);
}