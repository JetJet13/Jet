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
// Created by Johny Georges on 2025-06-09.
//

#include "ir-concat-expression-node.h"

IRConcatExpressionNode::IRConcatExpressionNode(std::shared_ptr<ASTConcatExpressionNode> astNode, llvm::CallInst* irValue, std::shared_ptr<IRExpressionNode> irLeftNode, std::shared_ptr<IRExpressionNode> irRightNode, std::shared_ptr<IRArrayPointerType> type) {
    _node = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
}

void IRConcatExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

llvm::CallInst* IRConcatExpressionNode::getValue() {
    return _irValue;
}

std::shared_ptr<IRExpressionNode> IRConcatExpressionNode::getLeftNode() {
    return _irLeftNode;
}

std::shared_ptr<IRExpressionNode> IRConcatExpressionNode::getRightNode() {
    return _irRightNode;
}

std::shared_ptr<IRType> IRConcatExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRConcatExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRConcatExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRConcatExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRConcatExpressionNode::getNodeType() {
    return IR_CONCAT_EXPRESSION_NODE;
}

std::string IRConcatExpressionNode::toString() {
    return "IR_CONCAT_EXPRESSION_NODE";
}

void IRConcatExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}