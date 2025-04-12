//
// Created by Johny Georges on 2025-04-12.
//

#include "type-value-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-type-value-type.h"
#include "../../../../shared/utils/logger/logger.h"

llvm::Value* TypeValueIRInjectorStrategy::inject(IRType* irType, IRBlockNode* irBlock) {
    if (irType->isArrayPointerType()) {
        return this->inject((IRArrayPointerType*)irType, irBlock);
    } else if (irType->isStructType()) {
        return this->inject((IRStructType*)irType, irBlock);
    } else if (irType->isPointerType()) {
        return this->inject((IRPointerType*)irType, irBlock);
    } else {
        return InstructionIRInjectorHelper::inject(irType->getValue(), irBlock);
    }
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRArrayPointerType* irArrayPointerType, IRBlockNode* irBlock) {
    auto irArrayTypeValue = InstructionIRInjectorHelper::inject(irArrayPointerType->getValue(), irBlock);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto elementTypeValue = this->inject(irArrayPointerType->getElementIRType(), irBlock);
    auto irTypeValueType = (IRTypeValueType*)irArrayPointerType->getValue()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(irTypeValueType->getAllocIndex());
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irTypeValueType->getType(), irArrayTypeValue, { zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(elementTypeValue, allocPointer);
    return irArrayTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRStructType* irStructType, IRBlockNode* irBlock) {
    auto irStructTypeValue = InstructionIRInjectorHelper::inject(irStructType->getValue(), irBlock);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irStructType->getValue()->getIRType()->getType(), irStructType->size());
    for (int i = 0; i < irStructType->size(); ++i) {
        auto index = irBlock->getBuilder()->get()->getInt32(i);
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto irTypeAtIndexValue = this->inject(irTypeAtIndex, irBlock);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, index });
        irBlock->getBuilder()->get()->CreateStore(irTypeAtIndexValue, pointer);
    }
    auto irTypeValueType = (IRTypeValueType*)irStructType->getValue()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(irTypeValueType->getAllocIndex());
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irTypeValueType->getType(), irStructTypeValue, { zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(allocation, allocPointer);
    return irStructTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRPointerType* irPointerType, IRBlockNode* irBlock) {
    auto irPointerTypeValue = InstructionIRInjectorHelper::inject(irPointerType->getValue(), irBlock);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto elementTypeValue = this->inject(irPointerType->getSourceType(), irBlock);
    auto irTypeValueType = (IRTypeValueType*)irPointerType->getValue()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(irTypeValueType->getAllocIndex());
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irTypeValueType->getType(), irPointerTypeValue, {zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(elementTypeValue, allocPointer);
    return irPointerTypeValue;
}