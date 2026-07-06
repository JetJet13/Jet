//
// Created by Johny Georges on 2026-02-14.
//

#include "ir-binary-operator-node.h"

IRBinaryOperatorNode::IRBinaryOperatorNode(llvm::BinaryOperator* irOp) {
    _irOp = irOp;
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

llvm::BinaryOperator* IRBinaryOperatorNode::getOp() {
    return _irOp;
}

bool IRBinaryOperatorNode::isHandled() {
    return _isHandled;
}

void IRBinaryOperatorNode::markAsHandled() {
    _isHandled = true;
}

int IRBinaryOperatorNode::getPriority() const {
    return _priority;
}

bool IRBinaryOperatorNode::isHigherPriorityThan(std::shared_ptr<IRBinaryOperatorNode> other) const {
    return _priority < other->getPriority();
}