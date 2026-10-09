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
// Created by Johny Georges on 2024-10-09.
//

#include "ir-tuple-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-type/ir-struct-ref-type.h"

IRTupleAccessExpressionNode::IRTupleAccessExpressionNode(std::shared_ptr<ASTTupleAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, uint64_t targetKeyIndex, llvm::Constant* irTargetKeyIndex, std::shared_ptr<IRType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

void IRTupleAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irSource->markAsGlobal();
}

std::optional<std::shared_ptr<IRInstructionNode>> IRTupleAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRTupleAccessExpressionNode::getArc() {
    return _irSource->getArc();
}

std::shared_ptr<IRExpressionNode> IRTupleAccessExpressionNode::getSource() {
    return _irSource;
}

llvm::Constant* IRTupleAccessExpressionNode::getIRTargetKeyIndex() {
    return _irTargetKeyIndex;
}

uint64_t IRTupleAccessExpressionNode::getTargetKeyIndex() {
    return _targetKeyIndex;
}

std::shared_ptr<IRType> IRTupleAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRTupleAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRTupleAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRTupleAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

std::shared_ptr<IRType> IRTupleAccessExpressionNode::getTargetIRType() {
    return std::dynamic_pointer_cast<IRStructRefType>(_irSource->getUnderlyingIRType())->getStructIRType()->getIRTypeByIndex(_targetKeyIndex);
}

llvm::Value* IRTupleAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRNodeType IRTupleAccessExpressionNode::getNodeType() {
    return IR_TUPLE_ACCESS_EXPRESSION_NODE;
}

std::string IRTupleAccessExpressionNode::toString() {
    return "IR_TUPLE_ACCESS_EXPRESSION_NODE";
}

void IRTupleAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
}