//
// Created by Johny Georges on 2025-04-12.
//

#include "type-value-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-type-value-type.h"
#include "../../../../shared/utils/logger/logger.h"

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (irType->getValue()->isInserted()) {
        return this->inject(irType->clone(), irBlock, irInjector, irModule);
    } else if (irType->isArrayPointerType()) {
        return this->inject(std::dynamic_pointer_cast<IRArrayPointerType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isStructType()) {
        return this->inject(std::dynamic_pointer_cast<IRStructType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isStructRefType()) {
        return this->inject(std::dynamic_pointer_cast<IRStructRefType>(irType), irBlock, irInjector, irModule);
    }else if (irType->isPointerType()) {
        return this->inject(std::dynamic_pointer_cast<IRPointerType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isRefType()) {
        return this->inject(std::dynamic_pointer_cast<IRRefType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isCapturedVariableType()) {
        return this->inject(std::dynamic_pointer_cast<IRCapturedVariableType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isLambdaType()) {
        return this->inject(std::dynamic_pointer_cast<IRLambdaType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isInvocableType()) {
        return this->inject(std::dynamic_pointer_cast<IRInvocableType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isClassInstanceType()) {
        return this->inject(std::dynamic_pointer_cast<IRClassInstanceType>(irType), irBlock, irInjector, irModule);
    } else if (irType->isNewClassInstanceType()) {
        return this->inject(std::dynamic_pointer_cast<IRNewClassInstanceType>(irType), irBlock, irInjector, irModule);
    } else {
        return InstructionIRInjectorHelper::inject(irType->getValue(), irBlock);
    }
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto irArrayTypeValue = InstructionIRInjectorHelper::inject(irArrayPointerType->getValue(), irBlock);
    auto elementTypeValue = this->inject(irArrayPointerType->getElementIRType(), irBlock, irInjector, irModule);
    auto irTypeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irArrayPointerType->getValue()->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irArrayTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(elementTypeValue, allocPointer, irBlock);
    return irArrayTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRStructType> irStructType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto typeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irStructType->getValue()->getIRType()->getSourceType());
    auto irStructTypeValue = InstructionIRInjectorHelper::inject(irStructType->getValue(), irBlock);
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irStructType->getValue()->getIRType()->getType(), irBlock->getBuilder()->get()->getInt64(irStructType->size()));
    for (unsigned long i = 0; i < irStructType->size(); ++i) {
        auto index = irBlock->getBuilder()->get()->getInt64(i);
        auto keyIdAtIndex = irStructType->getKeyIdForIndex(i);
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto irTypeAtIndexValue = this->inject(irTypeAtIndex, irBlock, irInjector, irModule);
        auto pointerToSizeInBytes = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), irTypeAtIndexValue, typeValueType->getSizeInBytesIndex());
        InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(irTypeAtIndex->getSizeInBytes()), pointerToSizeInBytes, irBlock);

        auto pointerToKeyId = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), irTypeAtIndexValue, typeValueType->getKeyIndex());
        InstructionIRInjectorHelper::injectStore(irInjector->injectStringGlobalVariable(irBlock, keyIdAtIndex, keyIdAtIndex, irModule), pointerToKeyId, irBlock);

        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { index });
        InstructionIRInjectorHelper::injectStore(irTypeAtIndexValue, pointer, irBlock);
    }
    auto irTypeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irStructType->getValue()->getIRType()->getSourceType());

    if (irStructType->hasId()) {
        auto pointerToValueId = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), irStructTypeValue, typeValueType->getValueIdIndex());
        InstructionIRInjectorHelper::injectStore(irInjector->injectStringGlobalVariable(irBlock, irStructType->getId() + ".id", irStructType->getId(), irModule), pointerToValueId, irBlock);
    }

    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irStructTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(allocation, allocPointer, irBlock);
    return irStructTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRPointerType> irPointerType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto irPointerTypeValue = InstructionIRInjectorHelper::inject(irPointerType->getValue(), irBlock);
    auto elementTypeValue = this->inject(irPointerType->getSourceType(), irBlock, irInjector, irModule);
    auto irTypeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irPointerType->getValue()->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irPointerTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(elementTypeValue, allocPointer, irBlock, irPointerType);
    return irPointerTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRRefType> irRefType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto irRefTypeValue = InstructionIRInjectorHelper::inject(irRefType->getValue(), irBlock);
    auto refValueTypeValue = this->inject(irRefType->getRefValueIRType(), irBlock, irInjector, irModule);
    auto irTypeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irRefType->getValue()->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irRefTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(refValueTypeValue, allocPointer, irBlock, irTypeValueType);
    return irRefTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRCapturedVariableType> irCapturedVariableType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto irCapturedVariableTypeValue = InstructionIRInjectorHelper::inject(irCapturedVariableType->getValue(), irBlock);
    auto capturedVariableTypeValue = this->inject(irCapturedVariableType->getVariableIRType()->getSourceType(), irBlock, irInjector, irModule);
    auto irTypeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irCapturedVariableType->getValue()->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irCapturedVariableTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(capturedVariableTypeValue, allocPointer, irBlock, irTypeValueType);
    return irCapturedVariableTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRStructRefType> irStructRefType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto irStructRefTypeValue = InstructionIRInjectorHelper::inject(irStructRefType->getValue(), irBlock);
    auto structRefTypeValue = this->inject(irStructRefType->getStructIRType(), irBlock, irInjector, irModule);
    auto irTypeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irStructRefType->getValue()->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(irTypeValueType->getType(), irStructRefTypeValue, irTypeValueType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(structRefTypeValue, allocPointer, irBlock, irTypeValueType);
    return irStructRefTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRInvocableType> irInvocableType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto typeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irInvocableType->getValue()->getIRType()->getSourceType());
    auto irInvocableTypeValue = InstructionIRInjectorHelper::inject(irInvocableType->getValue(), irBlock);
    auto parameters = irInvocableType->getParameters()->getParameters();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(typeValueType->getType(), irBlock->getBuilder()->get()->getInt64(1 + parameters->size()));
    auto returnTypeTypeValue = this->inject(irInvocableType->getReturnType(), irBlock, irInjector, irModule);
    auto returnTypePointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex });
    auto pointerToReturnTypeSizeInBytes = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), returnTypeTypeValue, typeValueType->getSizeInBytesIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(irInvocableType->getReturnType()->getSizeInBytes()), pointerToReturnTypeSizeInBytes, irBlock);
    InstructionIRInjectorHelper::injectStore(returnTypeTypeValue, returnTypePointer, irBlock);
    for (unsigned long i = 0; i < parameters->size(); ++i) {
        auto irTypeAtIndex = parameters->at(i);
        auto irTypeAtIndexValue = this->inject(irTypeAtIndex, irBlock, irInjector, irModule);
        auto pointerToSizeInBytes = irBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), irTypeAtIndexValue, typeValueType->getSizeInBytesIndex());
        InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(irTypeAtIndex->getSizeInBytes()), pointerToSizeInBytes, irBlock);
        auto index = irBlock->getBuilder()->get()->getInt64(i + 1); // index 0 is for the return type
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { index });
        InstructionIRInjectorHelper::injectStore(irTypeAtIndexValue, pointer, irBlock);
    }
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(typeValueType->getAllocIndex());
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), irInvocableTypeValue, { zeroIndex, allocIndex });
    InstructionIRInjectorHelper::injectStore(allocation, allocPointer, irBlock);
    return irInvocableTypeValue;
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRLambdaType> irLambdaType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    return this->inject(std::dynamic_pointer_cast<IRInvocableType>(irLambdaType->getLambdaVariableType()), irBlock, irInjector, irModule);
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRClassInstanceType> irClassInstanceType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    return this->inject(std::dynamic_pointer_cast<IRType>(irClassInstanceType->getIRClassPropertiesType()), irBlock, irInjector, irModule);
}

llvm::Value* TypeValueIRInjectorStrategy::inject(std::shared_ptr<IRNewClassInstanceType> irNewClassInstanceType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    return this->inject(std::dynamic_pointer_cast<IRType>(irNewClassInstanceType->getIRClassPropertiesType()), irBlock, irInjector, irModule);
}