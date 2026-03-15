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
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointerToProperty, irBlock);
    }
    return pointerToProperty;
}

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassStaticPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock);
    }
    return irExpression->getValue();
}