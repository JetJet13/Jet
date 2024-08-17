//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

llvm::Type* IRExpressionNode::getType() {
    return this->getValue()->getType();
}

llvm::Type* IRExpressionNode::getTypeAtIndex(unsigned long index) {
    return this->getValue()->getType();
}