//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-struct-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRStructExpressionInjectorStrategy::inject(IRStructExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto structRefAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto structAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue()->getParentAllocation().value(), irBlock);
    auto numElements = irExpression->size();
    for (unsigned long i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irTypeAtIndex = irExpression->getIRType()->getStructIRType()->getIRTypeByIndex(i);
        auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getStructIRType()->getType(), structAllocation, i);
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
        InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irTypeAtIndex);
    }

    auto pointerToStructPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getType(), structRefAllocation, irExpression->getIRType()->getStructIndex());
    InstructionIRInjectorHelper::injectStore(structAllocation, pointerToStructPointer, irBlock);
    auto pointerToCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getType(), structRefAllocation, irExpression->getIRType()->getCounterIndex());
    auto arc = InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
    InstructionIRInjectorHelper::injectStore(arc, pointerToCounterPointer, irBlock);

    if (irOperation->isOperandPointer()) {
        return structRefAllocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), structRefAllocation, irBlock, irExpression->getIRType());
}