//
// Created by Johny Georges on 2024-06-29.
//

#include <llvm/IR/Constant.h>
#include "ir-node.h"


llvm::Constant* IRNode::getConstantIRValue() {
    throw std::logic_error("getConstantIRValue not implemented for IR node: " + this->toString());
}