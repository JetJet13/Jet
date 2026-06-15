//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-access-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    auto irStructRefType = (IRStructRefType*)irExpression->getSource()->getIRType()->getSourceType()->getSourceType();
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(irExpression->getSource()->getAllocatedType(), irExpression->getValue(), irBlock);
    auto pointerToStructAlloc = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), loadedPointer, irStructRefType->getStructIndex());
    auto loadedStructAlloc = InstructionIRInjectorHelper::injectLoad(irExpression->getSource()->getAllocatedType(), pointerToStructAlloc, irBlock);
    auto pointerToProperty = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), loadedStructAlloc, irExpression->getTargetKeyIndex());
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getTargetIRType()->getType());
        auto typeValue = irInjector->inject(irBlock, irExpression->getTargetIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getCopyValueFunction(),
                { allocation, pointerToProperty, loadedTypeValue }
        );
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), allocation, irBlock);
    } else if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointerToProperty, irBlock, {}, "YUU");
    }
    return pointerToProperty;
}

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassStaticPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getSourceType()->getType());
        auto typeValue = irInjector->inject(irBlock, irExpression->getIRType()->getSourceType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getCopyValueFunction(),
                { allocation, irExpression->getValue(), loadedTypeValue }
        );
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), allocation, irBlock);
    } else if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock);
    }
    return irExpression->getValue();
}