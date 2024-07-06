//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-module-node.h"

IRModuleNode::IRModuleNode(llvm::Module* irValue) {
    _irValue = irValue;
}

llvm::Module* IRModuleNode::getModule() {
    return _irValue;
}