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
// Created by Johny Georges on 2026-02-13.
//

#include "ir-binary-arithmetic-node.h"

IRBinaryArithmeticNode::IRBinaryArithmeticNode(llvm::BinaryOperator* irOp, int leftOperandIndex, int rightOperandIndex) {
    _irOp = irOp;
    _leftOperandIndex = leftOperandIndex;
    _rightOperandIndex = rightOperandIndex;
    switch (_irOp->getOpcode()) {
        case llvm::Instruction::Add:
        case llvm::Instruction::FAdd:
        case llvm::Instruction::Sub:
        case llvm::Instruction::FSub:
            _priority = 2;
            break;
        case llvm::Instruction::Mul:
        case llvm::Instruction::FMul:
        case llvm::Instruction::SDiv:
        case llvm::Instruction::FDiv:
            _priority = 1;
            break;
        default:
            _priority = 10;
            break;
    }
}

llvm::BinaryOperator* IRBinaryArithmeticNode::getOp() {
    return _irOp;
}

int IRBinaryArithmeticNode::getLeftOperandIndex() {
    return _leftOperandIndex;
}

int IRBinaryArithmeticNode::getRightOperandIndex() {
    return _rightOperandIndex;
}

bool IRBinaryArithmeticNode::isHandled() {
    return _isHandled;
}

void IRBinaryArithmeticNode::markAsHandled() {
    _isHandled = true;
}

bool IRBinaryArithmeticNode::isIntAddition() {
    return _irOp->getOpcode() == llvm::Instruction::Add;
}

bool IRBinaryArithmeticNode::isIntSubtraction() {
    return _irOp->getOpcode() == llvm::Instruction::Sub;
}

bool IRBinaryArithmeticNode::isIntMultiplication() {
    return _irOp->getOpcode() == llvm::Instruction::Mul;
}

bool IRBinaryArithmeticNode::isFloatAddition() {
    return _irOp->getOpcode() == llvm::Instruction::FAdd;
}

bool IRBinaryArithmeticNode::isFloatSubtraction() {
    return _irOp->getOpcode() == llvm::Instruction::FSub;
}

bool IRBinaryArithmeticNode::isFloatMultiplication() {
    return _irOp->getOpcode() == llvm::Instruction::FMul;
}

int IRBinaryArithmeticNode::getPriority() const {
    return _priority;
}

bool IRBinaryArithmeticNode::isHigherPriorityThan(std::shared_ptr<IRBinaryArithmeticNode> other) const {
    return _priority < other->getPriority();
}