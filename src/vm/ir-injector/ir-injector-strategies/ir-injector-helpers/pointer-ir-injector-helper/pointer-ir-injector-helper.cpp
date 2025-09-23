//
// Created by Johny Georges on 2025-03-24.
//

#include "pointer-ir-injector-helper.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRInjectorHelper::injectPointerCopy(IRBlockNode* irBlock, IRPointerType* irPointerType, IRInstructionNode* sourceValueAllocation, IRModuleNode* irModule, IRInjector* irInjector) {
    auto loadedValue = InstructionIRInjectorHelper::injectLoad(sourceValueAllocation, irBlock);
    auto newValueAllocation = PointerIRInjectorHelper::injectPointerSourceAllocation(irBlock, irPointerType, loadedValue, irModule);
    auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getType());
    if (irPointerType->getUnderlyingType()->isArrayPointerType()) {
        auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(irBlock, sourceValueAllocation, irModule, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedArrayPointer->getValue(), newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//        irBlock->getBuilder()->get()->CreateStore(loadedArrayPointer->getValue(), newValueAllocation->getValue());
    } else if (irPointerType->getUnderlyingType()->isStructType()) {
        auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, sourceValueAllocation, irModule, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedNestedStruct, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//        irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, newValueAllocation->getValue());
    } else {
        InstructionIRInjectorHelper::injectStore(loadedValue, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//        irBlock->getBuilder()->get()->CreateStore(loadedValue, newValueAllocation->getValue());
    }
    InstructionIRInjectorHelper::injectStore(newValueAllocation->getValue(), newPointer, irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//    irBlock->getBuilder()->get()->CreateStore(newValueAllocation->getValue(), newPointer);
    return newPointer;
}

llvm::Value* PointerIRInjectorHelper::injectPointerCopy(IRBlockNode* irBlock, IRPointerType* irPointerType, llvm::Value* sourcePointer, IRModuleNode* irModule, IRInjector* irInjector) {
    auto loadedValue = InstructionIRInjectorHelper::injectLoad(irPointerType, sourcePointer, irBlock);
    auto newValueAllocation = PointerIRInjectorHelper::injectPointerSourceAllocation(irBlock, irPointerType, loadedValue, irModule);
    auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getType());
    if (irPointerType->getUnderlyingType()->isArrayPointerType()) {
        auto arrayPointerType = (IRArrayPointerType*)irPointerType->getUnderlyingType();
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType));
        auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule,  loadedValue, arrayPointerAllocation, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedArrayPointer->getValue(), newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getSourceType());
//        irBlock->getBuilder()->get()->CreateStore(loadedArrayPointer->getValue(), newValueAllocation->getValue());
    } else if (irPointerType->getUnderlyingType()->isStructType()) {
        auto structType = (IRStructType*)irPointerType->getSourceType();
        auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, structType, loadedValue, irModule, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedNestedStruct, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//        irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, newValueAllocation->getValue());
    } else {
        InstructionIRInjectorHelper::injectStore(loadedValue, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//        irBlock->getBuilder()->get()->CreateStore(loadedValue, newValueAllocation->getValue());
    }
    InstructionIRInjectorHelper::injectStore(newValueAllocation->getValue(), newPointer, irBlock, newValueAllocation->getIRType()->getUnderlyingType());
//    irBlock->getBuilder()->get()->CreateStore(newValueAllocation->getValue(), newPointer);
    return newPointer;
}

IRInstructionNode* PointerIRInjectorHelper::injectPointerSourceAllocation(IRBlockNode* irBlock, IRPointerType* irPointerType, llvm::Value* sourceValue, IRModuleNode* irModule) {

    if (irPointerType->getSourceType()->isArrayPointerType()) {
        auto irArrayPointerType = (IRArrayPointerType*)irPointerType->getSourceType();
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        auto numElementsIndex = irBlock->getBuilder()->get()->getInt64(irArrayPointerType->getNumElementsIndex());
        auto pointerToNumElements = irBlock->getBuilder()->get()->CreateInBoundsGEP(irArrayPointerType->getType(), sourceValue, { zeroIndex, numElementsIndex });
        auto numElements = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getNumElementsType(), pointerToNumElements);
        return ArrayIRInjectorHelper::injectArrayAllocation(irBlock, irArrayPointerType, numElements, irModule);
    }

    auto allocation = IRInstructionNodeFactory::create(irPointerType->getSourceType());
    irBlock->getBuilder()->get()->Insert(allocation->getValue());
    return allocation;
}