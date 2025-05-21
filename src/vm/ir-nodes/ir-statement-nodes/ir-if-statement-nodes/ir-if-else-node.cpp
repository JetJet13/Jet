//
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-else-node.h"

IRIfElseNode::IRIfElseNode(IRExpressionNode* condition, IRBlockNode* ifBlock, IRBlockNode* thenBlock, IRBlockNode* elseBlock, IRBlockNode* endBlock, std::optional<IRIfElseNode*> next) {
    _condition = condition;
    _ifBlock = ifBlock;
    _thenBlock = thenBlock;
    _elseBlock = elseBlock;
    _endBlock = endBlock;
    _next = next;
}

IRExpressionNode* IRIfElseNode::getExpression() {
    return _condition;
}

IRBlockNode* IRIfElseNode::getIfBlock() {
    return _ifBlock;
}

IRBlockNode* IRIfElseNode::getThenBlock() {
    return _thenBlock;
}

IRBlockNode* IRIfElseNode::getElseBlock() {
    return _elseBlock;
}

IRBlockNode* IRIfElseNode::getEndBlock() {
    return _endBlock;
}

void IRIfElseNode::setBlocksToBeSuccessorsOf(IRBlockNode* irBlock) {
    irBlock->addSuccessor(_ifBlock);
    irBlock->addSuccessor(_thenBlock);
    irBlock->addSuccessor(_elseBlock);
    irBlock->addSuccessor(_endBlock);
    if (_next) {
        _next.value()->setBlocksToBeSuccessorsOf(irBlock);
    }
}

void IRIfElseNode::setNext(IRIfElseNode* next) {
    _next = next;
}

std::optional<IRIfElseNode*> IRIfElseNode::getNext() {
    return _next;
}

IRNodeType IRIfElseNode::getNodeType() {
    return IR_IF_ELSE_NODE;
}

std::string IRIfElseNode::toString() {
    return "IR_IF_ELSE_NODE";
}

void IRIfElseNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _condition->print(stream);
}