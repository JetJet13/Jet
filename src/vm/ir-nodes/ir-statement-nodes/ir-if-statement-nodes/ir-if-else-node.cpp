//
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-else-node.h"

IRIfElseNode::IRIfElseNode(std::shared_ptr<IRExpressionNode> condition, std::shared_ptr<IRBlockNode> ifBlock, std::shared_ptr<IRBlockNode> thenBlock, std::shared_ptr<IRBlockNode> elseBlock, std::shared_ptr<IRBlockNode> endBlock, std::optional<std::shared_ptr<IRIfElseNode>> next) {
    _condition = condition;
    _ifBlock = ifBlock;
    _thenBlock = thenBlock;
    _elseBlock = elseBlock;
    _elseBlock->markAsFakeBlock();
    _endBlock = endBlock;
    _next = next;
}

std::shared_ptr<IRExpressionNode> IRIfElseNode::getExpression() {
    return _condition;
}

std::shared_ptr<IRBlockNode> IRIfElseNode::getIfBlock() {
    return _ifBlock;
}

std::shared_ptr<IRBlockNode> IRIfElseNode::getThenBlock() {
    return _thenBlock;
}

std::shared_ptr<IRBlockNode> IRIfElseNode::getElseBlock() {
    return _elseBlock;
}

std::shared_ptr<IRBlockNode> IRIfElseNode::getEndBlock() {
    return _endBlock;
}

void IRIfElseNode::nestIn(std::shared_ptr<IRBlockNode> irBlock) {
    irBlock->nest(_ifBlock);
    irBlock->nest(_thenBlock);
    irBlock->nest(_elseBlock);
    irBlock->nest(_endBlock);
    if (_next) {
        _next.value()->nestIn(irBlock);
    }
}

void IRIfElseNode::setNext(std::shared_ptr<IRIfElseNode> next) {
    _next = next;
}

std::optional<std::shared_ptr<IRIfElseNode>> IRIfElseNode::getNext() {
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