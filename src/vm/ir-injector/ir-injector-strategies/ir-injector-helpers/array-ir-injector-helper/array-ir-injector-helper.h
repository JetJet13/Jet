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
    static std::shared_ptr<IRLoadInstructionNode> injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::LoadInst* loadedNumElements, std::shared_ptr<IRInstructionNode> arrayPointerAllocation);
public:
    static std::shared_ptr<IRInstructionNode> injectArrayAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::Value* loadedNumElements, std::shared_ptr<IRModuleNode> irModule);
    static std::shared_ptr<IRInstructionNode> injectArrayPointerAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::Value* loadedNumElements, std::shared_ptr<IRModuleNode> irModule);
    static std::shared_ptr<IRLoadInstructionNode> injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, unsigned long numElements, std::shared_ptr<IRInstructionNode> arrayAllocation, std::shared_ptr<IRInstructionNode> arrayPointerAllocation);
    static std::shared_ptr<IRLoadInstructionNode> injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> sourceArrayPointerAllocation, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector);
    static std::shared_ptr<IRLoadInstructionNode> injectArrayCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, std::shared_ptr<IRType> elementType, std::shared_ptr<IRModuleNode> irModule, llvm::Value* sourceArray, std::shared_ptr<IRInstructionNode> arrayPointerAllocation, IRInjector* irInjector);
    static void injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::Value* numElements, llvm::Value* depth, llvm::Value* arrayPointerAllocation, llvm::Value* arrayAllocation);
    static llvm::Value* getPointerToIndexedElement(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayAccessExpressionNode> irAccessExpressionNode, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_ARRAY_IR_INJECTOR_HELPER_H
