//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        auto newRefAllocation = irBlock->getBuilder()->get()->CreateAlloca(irRefType->getType());
        auto typeValue = irInjector->inject(irBlock, irRefType->getRefValueIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyRefFunction(), { newRefAllocation, irExpression->getValue(), loadedTypeValue });
        return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), newRefAllocation, irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), irExpression->getValue(), irRefType->getRefValueIndex());
        auto loadedPointerToRefValue = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), loadedPointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() || irOperation->isFunctionArgument()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
        return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
    } else if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), irExpression->getValue(), irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else {
        return irExpression->getValue();
    }
}