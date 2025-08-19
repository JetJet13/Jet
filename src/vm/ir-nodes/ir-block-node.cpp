//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"
#include "../../shared/utils/logger/logger.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue) {
    _irValue = irValue;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
}

bool IRBlockNode::hasReturnStatement() {
    if (_body.empty()) {
        return false;
    }
    return _body.back()->is(IR_FUNCTION_RETURN_EXPRESSION_NODE);
}

bool IRBlockNode::hasBranchStatement() {
    return llvm::isa<llvm::BranchInst>(_irValue->back());
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

std::vector<IRNode*>* IRBlockNode::getBody() {
    return &_body;
}

void IRBlockNode::insert(IRNode* irNode) {
    _body.push_back(irNode);
}

std::unique_ptr<llvm::IRBuilder<>>* IRBlockNode::getBuilder() {
    return &_builder;
}

void IRBlockNode::addVoidReturn() {
    _builder.get()->CreateRetVoid();
}

void IRBlockNode::createSuccessor() {
    auto newBlock = new IRBlockNode(
        llvm::BasicBlock::Create(this->getBlock()->getContext(), "", this->getBlock()->getParent())
    );
    newBlock->setParentBlock(this);
    _successors.push_back(newBlock);
}

std::vector<IRBlockNode*>* IRBlockNode::getSuccessors() {
    return &_successors;
}

void IRBlockNode::addSuccessor(IRBlockNode* successorIrBlock) {
    _successors.push_back(successorIrBlock);
    successorIrBlock->setParentBlock(this);
    auto successorsOfSuccessorIrBlock = successorIrBlock->getSuccessors();
    for (int i = 0; i < successorsOfSuccessorIrBlock->size(); ++i) {
        _successors.push_back(successorsOfSuccessorIrBlock->at(i));
        successorsOfSuccessorIrBlock->at(i)->setParentBlock(this);
    }
}

IRBlockNode* IRBlockNode::getLastSuccessorOrSelf() {
    if (_successors.empty()) {
        return this;
    }
    return _successors.back();
}

std::optional<IRBlockNode*> IRBlockNode::getParentBlock() {
    return _parentBlock;
}

void IRBlockNode::setParentBlock(IRBlockNode* parentIRBlock) {
    _parentBlock = parentIRBlock;
}