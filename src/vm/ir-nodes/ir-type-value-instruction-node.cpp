//
// Created by Johny Georges on 2025-12-08.
//

#include "ir-type-value-instruction-node.h"
#include "../ir-type/ir-pointer-type.h"

IRTypeValueInstructionNode::IRTypeValueInstructionNode(llvm::AllocaInst* alloc, std::shared_ptr<IRPointerType> irType, llvm::StoreInst* initialValueStoreInstruction) {
    _alloc = alloc;
    _irType = irType;
    _initialValueStoreInstruction = initialValueStoreInstruction;
}

bool IRTypeValueInstructionNode::isInserted() {
    return _alloc->getParent() != nullptr;
}

llvm::AllocaInst* IRTypeValueInstructionNode::getValue() {
    return _alloc;
}

llvm::StoreInst* IRTypeValueInstructionNode::getInitialValueStoreInstruction() {
    return _initialValueStoreInstruction;
}

IRTypeValueInstructionNode* IRTypeValueInstructionNode::clone() {
    auto alloc = llvm::cast<llvm::AllocaInst>(_alloc->clone());
    auto storeInstruction = llvm::cast<llvm::StoreInst>(_initialValueStoreInstruction->clone());
    storeInstruction->setOperand(1, alloc);
    return new IRTypeValueInstructionNode(
            alloc,
            this->getIRType(),
            storeInstruction
    );
}

llvm::Type* IRTypeValueInstructionNode::getAllocatedType() {
    return _alloc->getAllocatedType();
}

llvm::MaybeAlign IRTypeValueInstructionNode::getAlignment() {
    return _alloc->getAlign();
}

uint64_t IRTypeValueInstructionNode::getSizeInBytes() {
    return _irType->getSourceType()->getSizeInBytes();
}

std::shared_ptr<IRPointerType> IRTypeValueInstructionNode::getIRType() {
    return _irType;
}