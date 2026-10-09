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
// Created by Johny Georges on 2024-08-05.
//

#include "ir-string-literal-expression-node.h"

IRStringLiteralExpressionNode::IRStringLiteralExpressionNode(std::shared_ptr<ASTLiteralExpressionNode> node, std::shared_ptr<IRStringLiteralNode> irValue, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRInstructionNode> sourceAllocation, std::shared_ptr<IRInstructionNode> arrayPointerSourceAllocation) {
    _node = node;
    _irValue = irValue;
    _irArrayPointerType = irArrayPointerType;
    _sourceAllocation = sourceAllocation;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
}

std::shared_ptr<IRArrayPointerType> IRStringLiteralExpressionNode::getIRArrayPointerType() {
    return _irArrayPointerType;
}

std::shared_ptr<IRType> IRStringLiteralExpressionNode::getIRType() {
    return _irArrayPointerType;
}

std::shared_ptr<TypeSignature> IRStringLiteralExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRStringLiteralExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRStringLiteralExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Constant* IRStringLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

std::optional<std::shared_ptr<IRInstructionNode>> IRStringLiteralExpressionNode::getSourceAllocation() {
    return _arrayPointerSourceAllocation;
}

std::shared_ptr<IRInstructionNode> IRStringLiteralExpressionNode::getSourceAggregateAllocation() {
    return _sourceAllocation;
}

std::shared_ptr<IRInstructionNode> IRStringLiteralExpressionNode::getAggregatePointerAllocation() {
    return _arrayPointerSourceAllocation;
}

IRNodeType IRStringLiteralExpressionNode::getNodeType() {
    return IR_STRING_LITERAL_EXPRESSION_NODE;
}

std::string IRStringLiteralExpressionNode::toString() {
    return "IR_STRING_LITERAL_EXPRESSION_NODE";
}

void IRStringLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}