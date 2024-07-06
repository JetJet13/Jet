//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-node.h"


bool IRNode::is(IRNodeType irNodeType) {
    return this->getNodeType() == irNodeType;
}

bool IRNode::isConstant() {
    return llvm::isa<llvm::Constant>(this->getIRValue());
}

llvm::Constant* IRNode::getConstantIRValue() {
    throw std::logic_error("getConstantIRValue not implemented for IR node: " + this->toString());
}

void IRNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    throw std::logic_error("insertSelfIntoBlock not implemented for IR node: " + this->toString());
}
