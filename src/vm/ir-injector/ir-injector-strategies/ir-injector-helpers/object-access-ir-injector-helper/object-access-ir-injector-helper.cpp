//
// Created by Johny Georges on 2025-12-19.
//

#include "object-access-ir-injector-helper.h"
#include "../../../../ir-type/ir-new-class-instance-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-class-instance-type.h"

llvm::Value* ObjectAccessIRInjectorHelper::getPointerToTarget(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRObjectAccessExpressionNode> irExpression, llvm::Value* sourceValue) {
    auto irType = irExpression->getSource()->getUnderlyingIRType();
    if (irType->isStructRefType()) {
        auto irStructRefType = std::dynamic_pointer_cast<IRStructRefType>(irType);
        auto pointerToStructAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), sourceValue, irStructRefType->getStructIndex());
        auto structAlloc = InstructionIRInjectorHelper::injectLoad(irStructRefType->getStructType(), pointerToStructAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), structAlloc, irExpression->getTargetKeyIndex());
    } else if (irType->isClassInstanceType()) {
        auto irStructRefType = (std::dynamic_pointer_cast<IRClassInstanceType>(irType)->getIRClassPropertiesType());
        auto pointerToStructAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), sourceValue, irStructRefType->getStructIndex());
        auto structAlloc = InstructionIRInjectorHelper::injectLoad(irStructRefType->getStructType(), pointerToStructAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), structAlloc, irExpression->getTargetKeyIndex());
    } else if (irType->isEnumType()) {
        auto enumGlobal = llvm::cast<llvm::GlobalVariable>(sourceValue);
        auto zero = irBlock->getBuilder()->get()->getInt64(0);
        auto index = irBlock->getBuilder()->get()->getInt64(irExpression->getTargetKeyIndex());
        auto pointer = llvm::GetElementPtrInst::Create(enumGlobal->getValueType(), enumGlobal, { zero, index });
        return irBlock->getBuilder()->get()->Insert(pointer);
    } else {
        auto irStructType = std::dynamic_pointer_cast<IRStructType>(irType);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), sourceValue, irExpression->getTargetKeyIndex());
    }
}

llvm::Value* ObjectAccessIRInjectorHelper::getPointerToTarget(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRTupleAccessExpressionNode> irExpression, llvm::Value* sourceValue) {
    auto irType = irExpression->getSource()->getUnderlyingIRType();
    if (irType->isStructRefType()) {
        auto irStructRefType = std::dynamic_pointer_cast<IRStructRefType>(irType);
        auto pointerToStructAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), sourceValue, irStructRefType->getStructIndex());
        auto structAlloc = InstructionIRInjectorHelper::injectLoad(irStructRefType->getStructType(), pointerToStructAlloc, irBlock);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), structAlloc, irExpression->getTargetKeyIndex());
    } else {
        auto irStructType = std::dynamic_pointer_cast<IRStructType>(irType);
        return irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), sourceValue, irExpression->getTargetKeyIndex());
    }
}