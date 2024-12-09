//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-constructor-node.h"

IRClassConstructorNode::IRClassConstructorNode(llvm::Function* irValue) {
    _irValue = irValue;
}

llvm::Function* IRClassConstructorNode::getFunction() {
    return _irValue;
}