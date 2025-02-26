//
// Created by Johny Georges on 2024-08-13.
//

#ifndef JETLANG_ARRAY_IR_INJECTOR_HELPER_H
#define JETLANG_ARRAY_IR_INJECTOR_HELPER_H

#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-aggregate-identifier-expression-node.h"
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../../ir-nodes/ir-module-node.h"
#include "../../../ir-injector.h"

class ArrayIRInjectorHelper {
private:
    static IRLoadInstructionNode* injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRInstructionNode* arrayPointerAllocation);
    static IRInstructionNode* injectArrayAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRModuleNode* irModule, IROperationType irOperationType);
public:
    static IRLoadInstructionNode* injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation);
    static IRLoadInstructionNode* injectArrayPointer(IRBlockNode* irBlock, IRInstructionNode* sourceArrayPointerAllocation, IRModuleNode* irModule, IROperationType irOperationType);
    static IRLoadInstructionNode* injectArrayCopy(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, IRType* elementType, IRModuleNode* irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation, IROperationType irOperationType);
    static IRLoadInstructionNode* injectArrayFromIdentifierExpression(IRAggregateIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRModuleNode* irModule, IROperationType irOperationType);
};

#endif //JETLANG_ARRAY_IR_INJECTOR_HELPER_H
