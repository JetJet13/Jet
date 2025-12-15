//
// Created by Johny Georges on 2025-12-08.
//

#ifndef JETLANG_IR_TYPE_VALUE_INSTRUCTION_NODE_H
#define JETLANG_IR_TYPE_VALUE_INSTRUCTION_NODE_H

#include <llvm/IR/Instructions.h>

// forward declaration
class IRBlockNode;
class IRPointerType;

class IRTypeValueInstructionNode {
private:
    llvm::AllocaInst* _alloc;
    IRPointerType* _irType;
    llvm::StoreInst* _initialValueStoreInstruction;
public:
    IRTypeValueInstructionNode(llvm::AllocaInst* alloc, IRPointerType* irType, llvm::StoreInst* initialValueStoreInstruction);
    bool isInserted();
    llvm::AllocaInst* getValue();
    llvm::StoreInst* getInitialValueStoreInstruction();
    IRTypeValueInstructionNode* clone();
    llvm::Type* getAllocatedType();
    llvm::MaybeAlign getAlignment();
    uint64_t getSizeInBytes();
    IRPointerType* getIRType();
};

#endif //JETLANG_IR_TYPE_VALUE_INSTRUCTION_NODE_H
