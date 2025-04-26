//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../pointer-ir-injector-helper/pointer-ir-injector-helper.h"

llvm::Value* StructIRInjectorHelper::injectStructCopy(IRBlockNode* irBlock, IRInstructionNode* structAllocation, IRModuleNode* irModule, IRInjector* irInjector) {
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
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getCopyValueFunction(),
                    {
                            destinationPointer,
                            arrayPointerAllocation->getValue(),
                            irTypeAtIndex->getValue()->getValue()
                    }
            );
        } else if (irTypeAtIndex->isStructType()) {
            auto nestedStructAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, nestedStructAllocation, irModule, irInjector);
            irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, destinationPointer);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, (IRPointerType*)irTypeAtIndex, pointerAllocation, irModule, irInjector);
            irBlock->getBuilder()->get()->CreateStore(loadedPointer, destinationPointer);
        } else {
            auto elementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
            auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(irTypeAtIndex->getType(), elementPointer);
            irBlock->getBuilder()->get()->CreateStore(loadedValue, destinationPointer);
        }
    }
    return irBlock->getBuilder()->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue());
}

llvm::Value* StructIRInjectorHelper::injectStructCopy(IRBlockNode* irBlock, IRStructType* irStructType, llvm::Value* structSource, IRModuleNode* irModule, IRInjector* irInjector) {
    auto destinationAllocation = irBlock->getBuilder()->get()->CreateAlloca(irStructType->getType());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = irBlock->getBuilder()->get()->getInt32(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation, { zeroIndex, index });
        auto pointerToStructValue = irBlock->getBuilder()->get()->CreateInBoundsGEP(irStructType->getType(), structSource, { zeroIndex, index });
        auto loadedPointerToStructValue = irBlock->getBuilder()->get()->CreateLoad(irTypeAtIndex->getType(), pointerToStructValue);
        if (irTypeAtIndex->isArrayPointerType()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getCopyValueFunction(),
                    {
                            destinationPointer,
                            pointerToStructValue,
                            irTypeAtIndex->getValue()->getValue()
                    }
            );
        } else if (irTypeAtIndex->isStructType()) {
            auto structType = (IRStructType*)irTypeAtIndex;
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(irBlock, structType, loadedPointerToStructValue, irModule, irInjector);
            irBlock->getBuilder()->get()->CreateStore(loadedNestedStruct, destinationPointer);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerType = (IRPointerType*)irTypeAtIndex;
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, loadedPointerToStructValue, irModule, irInjector);
            irBlock->getBuilder()->get()->CreateStore(loadedPointer, destinationPointer);
        } else {
            irBlock->getBuilder()->get()->CreateStore(loadedPointerToStructValue, destinationPointer);
        }
    }
    return irBlock->getBuilder()->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation);
}