// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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