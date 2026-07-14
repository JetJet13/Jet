//
// Created by Johny Georges on 2025-05-10.
//

#include "shared-ptr-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-shared-ptr-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* SharedPtrIRIdentifierExpressionInjectorStrategy::inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getIRType()->getSourceType());

    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), irExpression->getValue(), irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToSharedValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), irExpression->getValue(), irSharedPtrType->getSharedValueIndex());
        auto loadedPointerToSharedValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToSharedValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueIRType()->getType(), loadedPointerToSharedValue, irBlock);
    } else if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), irExpression->getValue(), irBlock);
    } else if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToSharedValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), irExpression->getValue(), irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToSharedValue, irBlock);
    } else {
        return irExpression->getValue();
    }
}