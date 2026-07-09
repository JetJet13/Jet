//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRIdentifierExpressionInjectorStrategy::inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());

    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
        return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), irExpression->getValue(), irRefType->getRefValueIndex());
        auto loadedPointerToRefValue = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), loadedPointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
        return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
    } else if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), irExpression->getValue(), irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else {
        return irExpression->getValue();
    }
}