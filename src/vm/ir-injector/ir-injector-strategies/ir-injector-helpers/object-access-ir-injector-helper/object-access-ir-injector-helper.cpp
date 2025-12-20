//
// Created by Johny Georges on 2025-12-19.
//

#include "object-access-ir-injector-helper.h"
#include "../../../../ir-type/ir-class-instance-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ObjectAccessIRInjectorHelper::getPointerToTarget(IRBlockNode* irBlock, IRObjectAccessExpressionNode* irExpression, llvm::Value* sourceValue) {
    auto irType = irExpression->getSource()->getUnderlyingIRType();
    if (irType->isClassInstanceType()) {
        auto irClassInstanceType = (IRClassInstanceType*)irType;
        auto pointerToClassInstanceAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irClassInstanceType->getIRClassPropertiesType()->getType(), sourceValue, irClassInstanceType->getIRClassPropertiesType()->getStructIndex());
        auto classInstanceAlloc = InstructionIRInjectorHelper::injectLoad(
                irClassInstanceType->getIRClassPropertiesType()->getStructType(), pointerToClassInstanceAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irClassInstanceType->getIRClassPropertiesType()->getStructIRType()->getType(), classInstanceAlloc, irExpression->getTargetKeyIndex());
    } else if (irType->isStructRefType()) {
        auto irStructRefType = (IRStructRefType*)irType;
        auto pointerToStructAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), sourceValue, irStructRefType->getStructIndex());
        auto structAlloc = InstructionIRInjectorHelper::injectLoad(irStructRefType->getStructType(), pointerToStructAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), structAlloc, irExpression->getTargetKeyIndex());
    } else {
        auto irStructType = (IRStructType*)irType;
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), sourceValue, irExpression->getTargetKeyIndex());
    }
}

llvm::Value* ObjectAccessIRInjectorHelper::getPointerToTarget(IRBlockNode* irBlock, IRTupleAccessExpressionNode* irExpression, llvm::Value* sourceValue) {
    auto irType = irExpression->getSource()->getUnderlyingIRType();
    if (irType->isClassInstanceType()) {
        auto irClassInstanceType = (IRClassInstanceType*)irType;
        auto pointerToClassInstanceAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irClassInstanceType->getIRClassPropertiesType()->getType(), sourceValue, irClassInstanceType->getIRClassPropertiesType()->getStructIndex());
        auto classInstanceAlloc = InstructionIRInjectorHelper::injectLoad(
                irClassInstanceType->getIRClassPropertiesType()->getStructType(), pointerToClassInstanceAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irClassInstanceType->getIRClassPropertiesType()->getStructIRType()->getType(), classInstanceAlloc, irExpression->getTargetKeyIndex());
    } else if (irType->isStructRefType()) {
        auto irStructRefType = (IRStructRefType*)irType;
        auto pointerToStructAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), sourceValue, irStructRefType->getStructIndex());
        auto structAlloc = InstructionIRInjectorHelper::injectLoad(irStructRefType->getStructType(), pointerToStructAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), structAlloc, irExpression->getTargetKeyIndex());
    } else {
        auto irStructType = (IRStructType*)irType;
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), sourceValue, irExpression->getTargetKeyIndex());
    }
}