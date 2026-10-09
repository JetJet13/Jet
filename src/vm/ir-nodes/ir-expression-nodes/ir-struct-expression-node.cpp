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
// Created by Johny Georges on 2024-07-01.
//

#include "ir-struct-expression-node.h"

IRStructExpressionNode::IRStructExpressionNode(std::shared_ptr<ASTStructExpressionNode> astNode, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc, std::shared_ptr<IRStructRefType> type, std::vector<std::shared_ptr<IRExpressionNode>> irValues) {
    _node = astNode;
    _irValue = irValue;
    _irArc = irArc;
    _irValues = irValues;
    _type = type;
}

void IRStructExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto irValue : _irValues) {
        irValue->markAsGlobal();
    }
}

std::shared_ptr<IRStructRefType> IRStructExpressionNode::getIRStructRefType() {
    return _type;
}

std::shared_ptr<IRType> IRStructExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRStructExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRStructExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRStructExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

std::optional<std::shared_ptr<IRInstructionNode>> IRStructExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRStructExpressionNode::getArc() {
    return _irArc;
}

uint64_t IRStructExpressionNode::size() {
    return _irValues.size();
}

llvm::Value* IRStructExpressionNode::getValue() {
    return _irValue->getValue();
}

std::shared_ptr<IRInstructionNode> IRStructExpressionNode::getIRValue() {
    return _irValue;
}

std::vector<std::shared_ptr<IRExpressionNode>>* IRStructExpressionNode::getValues() {
    return &_irValues;
}

IRNodeType IRStructExpressionNode::getNodeType() {
    return IR_STRUCT_EXPRESSION_NODE;
}

std::string IRStructExpressionNode::toString() {
    return "IR_STRUCT_EXPRESSION_NODE";
}

void IRStructExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}