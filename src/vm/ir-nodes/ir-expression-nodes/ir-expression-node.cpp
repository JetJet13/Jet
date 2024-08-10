//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"

llvm::Type* IRExpressionNode::getType() {
    return this->getValue()->getType();
}

llvm::Type* IRExpressionNode::getTypeAtIndex(unsigned long index) {
    return this->getValue()->getType();
}

std::optional<IRInstructionNode*> IRExpressionNode::getSourceAllocationAtIndex(unsigned long index) {
    if (this->getSourceAllocation()) {
        return this->getSourceAllocation().value()->getSourceAllocationAtIndex(index);
    }
    return {};
}

std::optional<IRInstructionNode*> IRExpressionNode::getSourceAllocation() {
    return {};
}