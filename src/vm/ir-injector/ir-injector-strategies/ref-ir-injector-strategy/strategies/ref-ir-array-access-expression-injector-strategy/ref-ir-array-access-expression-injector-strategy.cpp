//
// Created by Johny Georges on 2026-01-10.
//

#include "ref-ir-array-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* RefIRArrayAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRArrayAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType());
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointerAtIndex });
    }

    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), pointerAtIndex, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }

    return InstructionIRInjectorHelper::injectLoad(
            irRefType->getType(),
            pointerAtIndex,
            irBlock
    );
}