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
public:
    static IRInstructionNode* injectArrayAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* loadedNumElements, std::shared_ptr<IRModuleNode> irModule);
    static IRInstructionNode* injectArrayPointerAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* loadedNumElements, std::shared_ptr<IRModuleNode> irModule);
    static IRLoadInstructionNode* injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation);
    static IRLoadInstructionNode* injectArrayPointer(IRBlockNode* irBlock, IRInstructionNode* sourceArrayPointerAllocation, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector);
    static IRLoadInstructionNode* injectArrayCopy(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, IRType* elementType, std::shared_ptr<IRModuleNode> irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation, IRInjector* irInjector);
    static void injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* numElements, llvm::Value* depth, llvm::Value* arrayPointerAllocation, llvm::Value* arrayAllocation);
    static llvm::Value* getPointerToIndexedElement(IRBlockNode* irBlock, IRArrayAccessExpressionNode* irAccessExpressionNode, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector, IRLookupTable* scope);
};

#endif //JETLANG_ARRAY_IR_INJECTOR_HELPER_H
