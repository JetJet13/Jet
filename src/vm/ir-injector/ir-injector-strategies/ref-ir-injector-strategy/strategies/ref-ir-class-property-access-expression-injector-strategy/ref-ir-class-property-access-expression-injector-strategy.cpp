//
// Created by Johny Georges on 2026-06-13.
//

#include "ref-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"

llvm::Value* RefIRClassPropertyAccessExpressionInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    auto pointerToRef = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, new IROperation(IR_OPERAND_POINTER_OP));
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