//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    if (irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP) {
        auto newRefAllocation = irBlock->getBuilder()->get()->CreateAlloca(irRefType->getType());
        auto typeValue = irInjector->inject(irBlock, irRefType->getRefValueIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getValue()->getAllocatedType(), typeValue, irBlock);
//        auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irRefType->getRefValueIRType()->getValue()->getAllocatedType(), typeValue);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyRefFunction(), { newRefAllocation, irExpression->getValue(), loadedTypeValue });
        return newRefAllocation;
    }
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), irExpression->getValue(), irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    }
    return irExpression->getValue();
}