//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../pointer-ir-injector-helper/pointer-ir-injector-helper.h"

llvm::Value* StructIRInjectorHelper::injectStructCopy(IRBlockNode* irBlock, IRInstructionNode* structAllocation, IRModuleNode* irModule, IRInjector* irInjector) {
    auto destinationAllocation = IRInstructionNodeFactory::create(structAllocation);
    InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
    auto irStructType = (IRStructType*)structAllocation->getIRType()->getUnderlyingType();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = irBlock->getBuilder()->get()->getInt64(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation->getValue(), { zeroIndex, index });
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto typeValue = irInjector->inject(irBlock, irTypeAtIndex);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getValue()->getAllocatedType(), typeValue, irBlock, irTypeAtIndex);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getCopyArrayFunction(),
                    {
                        destinationPointer,
                        arrayPointerAllocation->getValue(),
                        loadedTypeValue
                    }
            );
        } else if (irTypeAtIndex->isStructType()) {
            auto nestedStructAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, nestedStructAllocation, irModule, irInjector);
            InstructionIRInjectorHelper::injectStore(loadedNestedStruct, destinationPointer, irBlock, irTypeAtIndex);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, (IRPointerType*)irTypeAtIndex, pointerAllocation, irModule, irInjector);
            InstructionIRInjectorHelper::injectStore(loadedPointer, destinationPointer, irBlock);
        } else {
            auto elementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
            auto loadedValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getType(), elementPointer, irBlock, irTypeAtIndex);
            InstructionIRInjectorHelper::injectStore(loadedValue, destinationPointer, irBlock);
        }
    }
    return InstructionIRInjectorHelper::injectLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue(), irBlock);
}

llvm::Value* StructIRInjectorHelper::injectStructCopy(IRBlockNode* irBlock, IRStructType* irStructType, llvm::Value* structSource, IRModuleNode* irModule, IRInjector* irInjector) {
    auto destinationAllocation = irBlock->getBuilder()->get()->CreateAlloca(irStructType->getType());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = irBlock->getBuilder()->get()->getInt64(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation, { zeroIndex, index });
        auto pointerToStructValue = irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), structSource, i);
        auto loadedPointerToStructValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getType(), pointerToStructValue, irBlock, irTypeAtIndex);
        if (irTypeAtIndex->isArrayPointerType()) {
            auto typeValue = irInjector->inject(irBlock, irTypeAtIndex);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getValue()->getAllocatedType(), typeValue, irBlock, irTypeAtIndex);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getCopyArrayFunction(),
                    {
                        destinationPointer,
                        pointerToStructValue,
                        loadedTypeValue
                    }
            );
        } else if (irTypeAtIndex->isStructType()) {
            auto structType = (IRStructType*)irTypeAtIndex;
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, structType, loadedPointerToStructValue, irModule, irInjector);
            InstructionIRInjectorHelper::injectStore(loadedNestedStruct, destinationPointer, irBlock, irTypeAtIndex);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerType = (IRPointerType*)irTypeAtIndex;
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, loadedPointerToStructValue, irModule, irInjector);
            InstructionIRInjectorHelper::injectStore(loadedPointer, destinationPointer, irBlock, irTypeAtIndex);
        } else {
            InstructionIRInjectorHelper::injectStore(loadedPointerToStructValue, destinationPointer, irBlock, irTypeAtIndex);
        }
    }
    return InstructionIRInjectorHelper::injectLoad(destinationAllocation->getAllocatedType(), destinationAllocation, irBlock, irStructType);
}