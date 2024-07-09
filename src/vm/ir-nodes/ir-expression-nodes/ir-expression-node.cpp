//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"

llvm::Type* IRExpressionNode::getIRType() {
    return this->getIRValue()->getType();
}

llvm::Type* IRExpressionNode::getIRTypeAtIndex(unsigned long index) {
    return this->getIRValue()->getType();
}