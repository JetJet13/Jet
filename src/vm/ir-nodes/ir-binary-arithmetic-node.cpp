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

bool IRBinaryArithmeticNode::isHigherPriorityThan(IRBinaryArithmeticNode* other) const {
    return _priority < other->getPriority();
}