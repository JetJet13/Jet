//
// Created by Johny Georges on 2024-08-13.
//

#ifndef JETLANG_ARRAY_IR_INJECTOR_HELPER_H
#define JETLANG_ARRAY_IR_INJECTOR_HELPER_H

#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-aggregate-identifier-expression-node.h"
#include "../../../../ir-nodes/ir-load-instruction-node.h"

class ArrayIRInjectorHelper {
public:
    static IRLoadInstructionNode* injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRInstructionNode* arrayPointerAllocation);
    static IRLoadInstructionNode* injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation);
    static IRLoadInstructionNode* injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* sourceArrayPointerAllocation);
    static void injectArrayCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* sourceAllocation, IRInstructionNode* destinationAllocation);
    static IRLoadInstructionNode* injectArrayFromIdentifierExpression(IRAggregateIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_ARRAY_IR_INJECTOR_HELPER_H
