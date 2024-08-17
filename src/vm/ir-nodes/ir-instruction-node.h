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
    std::optional<IRInstructionNode*> _parentAllocation;
    std::vector<IRInstructionNode*> _childAllocations;
    IRPointerType* _irType;
public:
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, IRInstructionNode* parentAllocation, std::vector<IRInstructionNode*> childAllocations);
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, std::optional<IRInstructionNode*> parentAllocation);
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations);
    IRInstructionNode(llvm::AllocaInst* irValue, IRPointerType* irType);
    explicit IRInstructionNode(llvm::GlobalVariable* irValue);
    llvm::Value* getValue();
    llvm::Type* getAllocatedType();
    IRInstructionNode* getParentAllocation();
    IRInstructionNode* getChildAllocationAtIndex(unsigned long index);
    llvm::MaybeAlign getAlignment();
    uint64_t getSizeInBytes();
    IRPointerType* getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INSTRUCTION_NODE_H
