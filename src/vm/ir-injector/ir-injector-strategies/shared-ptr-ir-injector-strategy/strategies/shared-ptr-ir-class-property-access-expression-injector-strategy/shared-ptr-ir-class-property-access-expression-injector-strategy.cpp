//
// Created by Johny Georges on 2026-06-13.
//

#include "shared-ptr-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-shared-ptr-type.h"

llvm::Value* SharedPtrIRClassPropertyAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getIRType()->getSourceType());
    auto pointerToRef = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), pointerToRef, irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return pointerToRef;
    }

    auto value = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), pointerToRef, irBlock);
    if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto underlyingValuePointer = irBlock->getBuilder()->get()->CreateExtractValue(value, irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueIRType()->getType(), underlyingValuePointer, irBlock, irSharedPtrType->getSharedValueIRType());
    } else if (irOperation->isOperandValue()) {
        return value;
    }
    irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointerToRef });
    return value;
}