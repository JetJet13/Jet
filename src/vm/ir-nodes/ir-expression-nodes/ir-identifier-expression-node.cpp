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
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(std::shared_ptr<ASTIdentifierExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, std::optional<std::shared_ptr<IRInstructionNode>> irArc) {
    _node = node;
    _irValue = irValue;
    _irArc = irArc;
    _irType = irValue->getIRType();
}

llvm::Value* IRIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

std::shared_ptr<IRInstructionNode> IRIdentifierExpressionNode::getIRValue() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRIdentifierExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRIdentifierExpressionNode::getArc() {
    return _irArc;
}

std::shared_ptr<IRType> IRIdentifierExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRIdentifierExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRIdentifierExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRIdentifierExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Type* IRIdentifierExpressionNode::getTypeAtIndex(uint64_t index) {
    auto type = _irValue->getIRType()->getUnderlyingType()->getType();
    if (type->isArrayTy()) {
        return type->getArrayElementType();
    } else if (type->isStructTy()) {
        return type->getStructElementType(index);
    } else {
        return type;
    }
}

IRNodeType IRIdentifierExpressionNode::getNodeType() {
    return IR_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRIdentifierExpressionNode::toString() {
    return "IR_IDENTIFIER_EXPRESSION_NODE";
}

void IRIdentifierExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}