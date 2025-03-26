//
// Created by Johny Georges on 2025-03-24.
//

#include "pointer-ir-injector-helper.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

// what are the semantics of copying a pointer?
// A. are you creating a new pointer that points to the source pointer's value?
// B. are you creating a new pointer to a copy of the source pointer's value?
//
// ANSWER
// =======
// B is the way to go, but we need to introduce a new keyword: sref to represent a shared reference
// otherwise, there won't be a way to create shared references
// e.g. const x = sref y; where y must have type ref<?>.
// const myStruct = { a: 1, b: ref [3, 5] };
// const myOtherStruct = myStruct where { b: sref myStruct.b };

llvm::Value* PointerIRInjectorHelper::injectPointerCopy(IRBlockNode* irBlock, IRPointerType* irPointerType, IRInstructionNode* sourceValueAllocation, IRModuleNode* irModule, IROperationType irOperationType) {
    // todo: implement answer above
    auto newValueAllocation = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getSourceType()->getType());
    auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getType());
    if (irPointerType->getSourceType()->isArrayPointerType()) {
        auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(irBlock, sourceValueAllocation, irModule, irOperationType);
        irBlock->getBuilder()->get()->CreateStore(loadedArrayPointer->getValue(), newValueAllocation);
    } else if (irPointerType->getSourceType()->isStructType()) {
        auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, sourceValueAllocation, irModule, irOperationType);
        irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, newValueAllocation);
    } else {
        auto loadedValue = InstructionIRInjectorHelper::injectLoad(sourceValueAllocation, irBlock);
        irBlock->getBuilder()->get()->CreateStore(loadedValue, newValueAllocation);
    }
    irBlock->getBuilder()->get()->CreateStore(newValueAllocation, newPointer);
    return newPointer;
}

llvm::Value* PointerIRInjectorHelper::injectPointerCopy(IRBlockNode* irBlock, IRPointerType* irPointerType, llvm::Value* sourcePointer, IRModuleNode* irModule, IROperationType irOperationType) {
    auto loadedValue = InstructionIRInjectorHelper::injectLoad(irPointerType, sourcePointer, irBlock);
    auto newValueAllocation = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getSourceType()->getType());
    auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getType());
    if (irPointerType->getSourceType()->isArrayPointerType()) {
        auto arrayPointerType = (IRArrayPointerType*)irPointerType->getSourceType();
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType));
        auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule,  loadedValue, arrayPointerAllocation, irOperationType);
        irBlock->getBuilder()->get()->CreateStore(loadedArrayPointer->getValue(), newValueAllocation);
    } else if (irPointerType->getSourceType()->isStructType()) {
        auto structType = (IRStructType*)irPointerType->getSourceType();
        auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, structType, loadedValue, irModule, irOperationType);
        irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, newValueAllocation);
    } else {
        irBlock->getBuilder()->get()->CreateStore(loadedValue, newValueAllocation);
    }
    irBlock->getBuilder()->get()->CreateStore(newValueAllocation, newPointer);
    return newPointer;
}