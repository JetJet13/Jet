//
// Created by Johny Georges on 2025-04-12.
//

#include "type-value-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-type-value-type.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-type/ir-function-parameter-type.h"

llvm::Value* TypeValueIRInjectorStrategy::inject(IRType* irType, IRBlockNode* irBlock) {
    if (irType->getValue()->isInserted()) {
        Logger::log("IS INSERTED TYPE VALUE!");
        return irType->getValue()->getValue();
    } else if (irType->isArrayPointerType()) {
        return this->inject((IRArrayPointerType*)irType, irBlock);
    } else if (irType->isStructType()) {
        return this->inject((IRStructType*)irType, irBlock);
    } else if (irType->isPointerType()) {
        return this->inject((IRPointerType*)irType, irBlock);
    } else if (irType->isRefType()) {
        return this->inject((IRRefType*)irType, irBlock);
    } else if (irType->isCapturedVariableType()) {
        return this->inject((IRCapturedVariableType*)irType, irBlock);
    } else if (irType->isFunctionParameterType()) {
        return this->inject((IRFunctionParameterType*)irType, irBlock);
    } else if (irType->isClassInstanceType()) {
        return this->inject((IRClassInstanceType*)irType, irBlock);
    } else {
        return InstructionIRInjectorHelper::inject(irType->getValue(), irBlock);
    }
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRArrayPointerType* irArrayPointerType, IRBlockNode* irBlock) {
    auto irArrayTypeValue = InstructionIRInjectorHelper::inject(irArrayPointerType->getValue(), irBlock);
    auto elementTypeValue = this->inject(irArrayPointerType->getElementIRType(), irBlock);
    auto irTypeValueType = (IRTypeValueType*)irArrayPointerType->getValue()->getIRType()->getSourceType();
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irArrayTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(elementTypeValue, allocPointer, irBlock);
    return irArrayTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRStructType* irStructType, IRBlockNode* irBlock) {
    auto typeValueType = (IRTypeValueType*)irStructType->getValue()->getIRType()->getSourceType();
    auto irStructTypeValue = InstructionIRInjectorHelper::inject(irStructType->getValue(), irBlock);
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irStructType->getValue()->getIRType()->getType(), irBlock->getBuilder()->get()->getInt64(irStructType->size()));
    for (int i = 0; i < irStructType->size(); ++i) {
        auto index = irBlock->getBuilder()->get()->getInt64(i);
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto irTypeAtIndexValue = this->inject(irTypeAtIndex, irBlock);
        auto pointerToSizeInBytes = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), irTypeAtIndexValue, typeValueType->getSizeInBytesIndex());
        InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(irTypeAtIndex->getSizeInBytes()), pointerToSizeInBytes, irBlock);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { index });
        InstructionIRInjectorHelper::injectStore(irTypeAtIndexValue, pointer, irBlock);
    }
    auto irTypeValueType = (IRTypeValueType*)irStructType->getValue()->getIRType()->getSourceType();
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irStructTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(allocation, allocPointer, irBlock);
    return irStructTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRPointerType* irPointerType, IRBlockNode* irBlock) {
    auto irPointerTypeValue = InstructionIRInjectorHelper::inject(irPointerType->getValue(), irBlock);
    auto elementTypeValue = this->inject(irPointerType->getSourceType(), irBlock);
    auto irTypeValueType = (IRTypeValueType*)irPointerType->getValue()->getIRType()->getSourceType();
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irPointerTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(elementTypeValue, allocPointer, irBlock, irPointerType);
    return irPointerTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRRefType* irRefType, IRBlockNode* irBlock) {
    auto irRefTypeValue = InstructionIRInjectorHelper::inject(irRefType->getValue(), irBlock);
    auto refValueTypeValue = this->inject(irRefType->getRefValueIRType(), irBlock);
    auto irTypeValueType = (IRTypeValueType*)irRefType->getValue()->getIRType()->getSourceType();
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irRefTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(refValueTypeValue, allocPointer, irBlock, irTypeValueType);
    return irRefTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRCapturedVariableType* irCapturedVariableType, IRBlockNode* irBlock) {
    auto irCapturedVariableTypeValue = InstructionIRInjectorHelper::inject(irCapturedVariableType->getValue(), irBlock);
    auto capturedVariableTypeValue = this->inject(irCapturedVariableType->getVariableIRType()->getSourceType(), irBlock);
    auto irTypeValueType = (IRTypeValueType*)irCapturedVariableType->getValue()->getIRType()->getSourceType();
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irCapturedVariableTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(capturedVariableTypeValue, allocPointer, irBlock, irTypeValueType);
    return irCapturedVariableTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRFunctionParameterType* irFunctionParameterType, IRBlockNode* irBlock) {
    auto typeValueType = (IRTypeValueType*)irFunctionParameterType->getValue()->getIRType()->getSourceType();
    auto irFunctionParameterTypeValue = InstructionIRInjectorHelper::inject(irFunctionParameterType->getValue(), irBlock);
    auto parameters = irFunctionParameterType->getParameters()->getParameters();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(typeValueType->getType(), irBlock->getBuilder()->get()->getInt64(1 + parameters->size()));
    auto returnTypeTypeValue = this->inject(irFunctionParameterType->getReturnType(), irBlock);
    auto returnTypePointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex });
    auto pointerToReturnTypeSizeInBytes = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), returnTypeTypeValue, typeValueType->getSizeInBytesIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(irFunctionParameterType->getReturnType()->getSizeInBytes()), pointerToReturnTypeSizeInBytes, irBlock);
    InstructionIRInjectorHelper::injectStore(returnTypeTypeValue, returnTypePointer, irBlock);
    for (int i = 0; i < parameters->size(); ++i) {
        auto irTypeAtIndex = parameters->at(i);
        auto irTypeAtIndexValue = this->inject(irTypeAtIndex, irBlock);
        auto pointerToSizeInBytes = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), irTypeAtIndexValue, typeValueType->getSizeInBytesIndex());
        InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(irTypeAtIndex->getSizeInBytes()), pointerToSizeInBytes, irBlock);
        auto index = irBlock->getBuilder()->get()->getInt64(i + 1); // index 0 is for the return type
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { index });
        InstructionIRInjectorHelper::injectStore(irTypeAtIndexValue, pointer, irBlock);
    }
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(typeValueType->getAllocIndex());
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), irFunctionParameterTypeValue, { zeroIndex, allocIndex });
    InstructionIRInjectorHelper::injectStore(allocation, allocPointer, irBlock);
    return irFunctionParameterTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRLambdaType* irLambdaType, IRBlockNode* irBlock) {
    return this->inject((IRType*)irLambdaType->getLambdaVariableType(), irBlock);
}

llvm::Value* TypeValueIRInjectorStrategy::inject(IRClassInstanceType* irClassInstanceType, IRBlockNode* irBlock) {
    return this->inject((IRType*)irClassInstanceType->getIRClassPropertiesType(), irBlock);
}