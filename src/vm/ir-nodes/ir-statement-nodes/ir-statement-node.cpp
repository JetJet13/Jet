//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-statement-node.h"

llvm::Type* IRStatementNode::getIRType() {
    return this->getIRValue()->getType();
}

llvm::Type* IRStatementNode::getIRTypeAtIndex(unsigned long index) {
    return this->getIRValue()->getType();
}