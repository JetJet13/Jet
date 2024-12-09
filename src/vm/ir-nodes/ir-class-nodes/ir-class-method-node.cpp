//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-method-node.h"

IRClassMethodNode::IRClassMethodNode(llvm::Function* irValue) {
    _irValue = irValue;
}

llvm::Function* IRClassMethodNode::getFunction() {
    return _irValue;
}