//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-node.h"

llvm::Type* IRLiteralNode::getType() {
    return this->getConstantIRValue()->getType();
}