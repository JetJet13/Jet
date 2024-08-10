//
// Created by Johny Georges on 2024-08-09.
//

#ifndef JETLANG_IR_ARRAY_POINTER_SUPPORT_FUNCTION_H
#define JETLANG_IR_ARRAY_POINTER_SUPPORT_FUNCTION_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Intrinsics.h>
#include <utility>
#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-type/ir-array-pointer-type.h"

class IRArrayPointerSupportFunction {
public:
    static llvm::LoadInst* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayPointerAllocation);
    static llvm::LoadInst* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType,  IRInstructionNode* arrayAllocation, llvm::AllocaInst* arrayPointerAllocation);
};


#endif //JETLANG_IR_ARRAY_POINTER_SUPPORT_FUNCTION_H
