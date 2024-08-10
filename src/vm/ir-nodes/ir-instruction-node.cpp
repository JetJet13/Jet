//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"
#include <utility>

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, std::optional<IRInstructionNode*> sourceAllocation) {
    _irValue = irValue;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
    _childSourceAllocations = std::vector<IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, IRInstructionNode* sourceAllocation, std::vector<IRInstructionNode*> childSourceAllocations) {
    _irValue = irValue;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
    _childSourceAllocations = std::move(childSourceAllocations);
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childSourceAllocations) {
    _irValue = irValue;
    _irType = irType;
    _sourceAllocation = {};
    _childSourceAllocations = std::move(childSourceAllocations);
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType) {
    _irValue = irValue;
    _irType = irType;
    _sourceAllocation = {};
    _childSourceAllocations = std::vector<IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::GlobalVariable* irValue) {
    _irValue = irValue;
    _irType = IRPointerType::create(irValue);
    _sourceAllocation = {};
    _childSourceAllocations = std::vector<IRInstructionNode*>();
}

llvm::Value* IRInstructionNode::getValue() {
    return _irValue;
}

IRInstructionNode* IRInstructionNode::getSourceAllocation() {
    if (_sourceAllocation) {
        return _sourceAllocation.value();
    }
    return this;
}

llvm::Type* IRInstructionNode::getAllocatedType() {
    if (llvm::isa<llvm::AllocaInst>(_irValue)) {
        return llvm::cast<llvm::AllocaInst>(_irValue)->getAllocatedType();
    }
    return llvm::cast<llvm::GlobalVariable>(_irValue)->getValueType();
}

IRInstructionNode* IRInstructionNode::getSourceAllocationAtIndex(unsigned long index) {
    return _childSourceAllocations[index];
}

llvm::MaybeAlign IRInstructionNode::getAlignment() {
    if (llvm::isa<llvm::AllocaInst>(_irValue)) {
        return llvm::cast<llvm::AllocaInst>(_irValue)->getAlign();
    }
    return llvm::cast<llvm::GlobalVariable>(_irValue)->getAlign();
}

uint64_t IRInstructionNode::getSizeInBytes() {
    return _irType->getSourceType()->getSizeInBytes();
}

IRPointerType* IRInstructionNode::getIRType() {
    return _irType;
}

IRNodeType IRInstructionNode::getNodeType() {
    return IR_ALLOCATION_NODE;
}

std::string IRInstructionNode::toString() {
    return "IR_ALLOCATION_NODE";
}

void IRInstructionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}