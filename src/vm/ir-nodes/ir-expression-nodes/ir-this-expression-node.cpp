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
// Created by Johny Georges on 2026-06-15.
//

#include "ir-this-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRThisExpressionNode::IRThisExpressionNode(std::shared_ptr<ASTThisExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue) {
    _node = node;
    _irValue = irValue;
    _irType = std::dynamic_pointer_cast<IRPointerType>(irValue->getIRType()->getSourceType());
}

llvm::Value* IRThisExpressionNode::getValue() {
    return _irValue->getValue();
}

std::shared_ptr<IRInstructionNode> IRThisExpressionNode::getIRValue() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRThisExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::shared_ptr<IRType> IRThisExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRThisExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRThisExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRThisExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRThisExpressionNode::getNodeType() {
    return IR_THIS_EXPRESSION_NODE;
}

std::string IRThisExpressionNode::toString() {
    return "IR_THIS_EXPRESSION_NODE";
}

void IRThisExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}