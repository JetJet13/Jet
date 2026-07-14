//
// Created by Johny Georges on 2026-01-10.
//

#include "shared-ptr-ir-array-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../../ir-type/ir-shared-ptr-type.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* SharedPtrIRArrayAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRArrayAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getIRType());
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointerAtIndex });
    }

    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToSharedValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), pointerAtIndex, irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToSharedValue, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }

    return InstructionIRInjectorHelper::injectLoad(
            irSharedPtrType->getType(),
            pointerAtIndex,
            irBlock
    );
}