//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-function-node.h"
#include "../ir-block-node.h"
#include <llvm/IR/GlobalIFunc.h>

IRFunctionNode::IRFunctionNode(llvm::Function* irValue) {
    _irValue = irValue;
}

llvm::Function* IRFunctionNode::getFunction() {
    return _irValue;
}