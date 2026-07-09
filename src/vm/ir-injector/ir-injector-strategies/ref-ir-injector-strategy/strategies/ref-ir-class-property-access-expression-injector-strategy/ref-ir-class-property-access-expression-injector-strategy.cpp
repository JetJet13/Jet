//
// Created by Johny Georges on 2026-06-13.
//

#include "ref-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"

llvm::Value* RefIRClassPropertyAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());
    auto pointerToRef = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), pointerToRef, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return pointerToRef;
    }

    auto value = InstructionIRInjectorHelper::injectLoad(irRefType->getType(), pointerToRef, irBlock);
    if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto underlyingValuePointer = irBlock->getBuilder()->get()->CreateExtractValue(value, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), underlyingValuePointer, irBlock, irRefType->getRefValueIRType());
    } else if (irOperation->isOperandValue()) {
        return value;
    }
    irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointerToRef });
    return value;
}