//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-type/ir-struct-type.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"

IRLoadInstructionNode* StructIRInjectorHelper::injectStruct(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* structAllocation) {
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
            auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerAllocation);
            builder->get()->CreateStore(loadedArrayPointer->getValue(), destinationPointer);
        } else if (irTypeAtIndex->isStructType()) {
            auto nestedStructAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStruct(builder, nestedStructAllocation);
            builder->get()->CreateStore(loadedNestedStruct->getValue(), destinationPointer);
        } else {
                auto elementPointer = builder->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
                auto loadedValue = builder->get()->CreateLoad(irTypeAtIndex->getType(), elementPointer);
                builder->get()->CreateStore(loadedValue, destinationPointer);
            }
    }
    return new IRLoadInstructionNode(builder->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue()), destinationAllocation);
}