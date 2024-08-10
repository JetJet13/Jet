//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_H
#define JETLANG_IR_INSTRUCTION_NODE_H

#include "ir-node.h"
#include "../ir-type/ir-type.h"
#include "../ir-type/ir-pointer-type.h"

class IRInstructionNode : public IRNode {
private:
    llvm::Value* _irValue;
    std::optional<IRInstructionNode*> _sourceAllocation;
    std::vector<IRInstructionNode*> _childSourceAllocations;
    IRPointerType* _irType;
public:
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, IRInstructionNode* sourceAllocation, std::vector<IRInstructionNode*> childSourceAllocations);
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, std::optional<IRInstructionNode*> sourceAllocation);
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childSourceAllocations);
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType);
    explicit IRInstructionNode(llvm::GlobalVariable* irValue);
    llvm::Value* getValue();
    llvm::Type* getAllocatedType();
    IRInstructionNode* getSourceAllocation();
    IRInstructionNode* getSourceAllocationAtIndex(unsigned long index);
    llvm::MaybeAlign getAlignment();
    uint64_t getSizeInBytes();
    IRPointerType* getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INSTRUCTION_NODE_H
