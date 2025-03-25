//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../pointer-ir-injector-helper/pointer-ir-injector-helper.h"

llvm::Value* StructIRInjectorHelper::injectStructCopy(IRBlockNode* irBlock, IRInstructionNode* structAllocation, IRModuleNode* irModule, IROperationType irOperationType) {
    auto destinationAllocation = IRInstructionNodeFactory::create(structAllocation);
    InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
    auto irStructType = (IRStructType*)structAllocation->getIRType()->getSourceType();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = irBlock->getBuilder()->get()->getInt32(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation->getValue(), { zeroIndex, index });
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerAllocation, irModule, irOperationType);
            irBlock->getBuilder()->get()->CreateStore(loadedArrayPointer->getValue(), destinationPointer);
        } else if (irTypeAtIndex->isStructType()) {
            auto nestedStructAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, nestedStructAllocation, irModule, irOperationType);
            irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, destinationPointer);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto elementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, (IRPointerType*)irTypeAtIndex, elementPointer, pointerAllocation, irModule, irOperationType);
            irBlock->getBuilder()->get()->CreateStore(loadedPointer, destinationPointer);
        } else {
            auto elementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
            auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(irTypeAtIndex->getType(), elementPointer);
            irBlock->getBuilder()->get()->CreateStore(loadedValue, destinationPointer);
        }
    }
    return irBlock->getBuilder()->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue());
}

llvm::Value* StructIRInjectorHelper::injectStructCopy(IRBlockNode* irBlock, IRStructType* irStructType, llvm::Value* structSource, IRModuleNode* irModule, IROperationType irOperationType) {
    auto destinationAllocation = irBlock->getBuilder()->get()->CreateAlloca(irStructType->getType());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = irBlock->getBuilder()->get()->getInt32(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation, { zeroIndex, index });
        auto pointerToStructValue = irBlock->getBuilder()->get()->CreateInBoundsGEP(irStructType->getType(), structSource, { zeroIndex, index });
        auto loadedPointerToStructValue = irBlock->getBuilder()->get()->CreateLoad(irTypeAtIndex->getType(), pointerToStructValue);
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerType = (IRArrayPointerType*)irTypeAtIndex;
            auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType));
            auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule, loadedPointerToStructValue, arrayPointerAllocation, irOperationType);
            irBlock->getBuilder()->get()->CreateStore(loadedArrayPointer->getValue(), destinationPointer);
        } else if (irTypeAtIndex->isStructType()) {
            auto structType = (IRStructType*)irTypeAtIndex;
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, structType, loadedPointerToStructValue, irModule, irOperationType);
            irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, destinationPointer);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerType = (IRPointerType*)irTypeAtIndex;
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, loadedPointerToStructValue, irModule, irOperationType);
            irBlock->getBuilder()->get()->CreateStore(loadedPointer, destinationPointer);
        } else {
            irBlock->getBuilder()->get()->CreateStore(loadedPointerToStructValue, destinationPointer);
        }
    }
    return irBlock->getBuilder()->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation);
}