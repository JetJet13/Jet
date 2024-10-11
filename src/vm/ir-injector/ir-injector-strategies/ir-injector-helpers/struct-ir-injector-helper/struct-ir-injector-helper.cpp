//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"

llvm::Value* StructIRInjectorHelper::injectStructCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* structAllocation, IRModuleNode* irModule) {
    auto destinationAllocation = IRInstructionNodeFactory::create(structAllocation);
    builder->get()->Insert(destinationAllocation->getValue());
    auto irStructType = (IRStructType*)structAllocation->getIRType()->getSourceType();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = builder->get()->getInt32(i);
        auto destinationPointer = builder->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation->getValue(), { zeroIndex, index });
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerAllocation, irModule);
            builder->get()->CreateStore(loadedArrayPointer->getValue(), destinationPointer);
        } else if (irTypeAtIndex->isStructType()) {
            auto nestedStructAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(builder, nestedStructAllocation, irModule);
            builder->get()->CreateStore(loadedNestedStruct, destinationPointer);
        } else {
            auto elementPointer = builder->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
            auto loadedValue = builder->get()->CreateLoad(irTypeAtIndex->getType(), elementPointer);
            builder->get()->CreateStore(loadedValue, destinationPointer);
        }
    }
    return builder->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue());
}

llvm::Value* StructIRInjectorHelper::injectStructCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRStructType* irStructType, llvm::Value* structSource, IRModuleNode* irModule) {
    auto destinationAllocation = builder->get()->CreateAlloca(irStructType->getType());
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = builder->get()->getInt32(i);
        auto destinationPointer = builder->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation, { zeroIndex, index });
        auto pointerToStructValue = builder->get()->CreateInBoundsGEP(structSource->getType(), structSource, { zeroIndex, index });
        auto loadedPointerToStructValue = builder->get()->CreateLoad(irTypeAtIndex->getType(), pointerToStructValue);
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerType = (IRArrayPointerType*)irTypeAtIndex;
            auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType));
            auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayCopy(builder, arrayPointerType, arrayPointerType->getElementIRType(), irModule, loadedPointerToStructValue, arrayPointerAllocation);
            builder->get()->CreateStore(loadedArrayPointer->getValue(), destinationPointer);
        } else if (irTypeAtIndex->isStructType()) {
            auto irStructTypeAtIndex = (IRStructType*)irTypeAtIndex;
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructCopy(builder, irStructTypeAtIndex, loadedPointerToStructValue, irModule);
            builder->get()->CreateStore(loadedNestedStruct, destinationPointer);
        } else {
            builder->get()->CreateStore(loadedPointerToStructValue, destinationPointer);
        }
    }
    return builder->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation);
}