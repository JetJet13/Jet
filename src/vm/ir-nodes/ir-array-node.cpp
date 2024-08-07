//
// Created by Johny Georges on 2024-08-05.
//

#include "ir-array-node.h"

IRArrayNode::IRArrayNode(IRPointerType* type, unsigned long size, llvm::AllocaInst* allocation) {
    _type = type;
    _size = size;
    _allocation = allocation;
}

llvm::Value* IRArrayNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value* arrayAllocation) {
    auto arrayObjectAllocation = builder->get()->Insert(_allocation);
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(0);
    auto pointerIndex = builder->get()->getInt32(1);
    auto intPointer = builder->get()->CreateInBoundsGEP(_type->getPointerSourceIRType()->getType(), arrayObjectAllocation, { zeroIndex, intIndex });
    builder->get()->CreateStore(builder->get()->getInt32(_size), intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(_type->getPointerSourceIRType()->getType(), arrayObjectAllocation, { zeroIndex, pointerIndex });
    builder->get()->CreateStore(arrayAllocation, arrayPointer);
    return arrayObjectAllocation;
}

IRPointerType* IRArrayNode::getIRType() {
    return _type;
}

unsigned long IRArrayNode::getSize() {
    return _size;
}

IRNodeType IRArrayNode::getNodeType() {
    return IR_ARRAY_NODE;
}

std::string IRArrayNode::toString() {
    return "IR_ARRAY_NODE";
}

void IRArrayNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _allocation->print(**stream);
}