//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

std::optional<IRInstructionNode*> IRExpressionNode::getSourceAllocation() {
    return {};
}

llvm::Type* IRExpressionNode::getType() {
    return this->getValue()->getType();
}

llvm::Type* IRExpressionNode::getTypeAtIndex(unsigned long index) {
    return this->getValue()->getType();
}