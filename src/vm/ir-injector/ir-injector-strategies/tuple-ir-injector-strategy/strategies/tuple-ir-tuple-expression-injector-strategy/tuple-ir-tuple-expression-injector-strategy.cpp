//
// Created by Johny Georges on 2025-03-08.
//

#include "tuple-ir-tuple-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* TupleIRTupleExpressionInjectorStrategy::inject(IRTupleExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto tupleRefAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto tupleAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue()->getParentAllocation().value(), irBlock);
    auto numElements = irExpression->size();
    for (unsigned long i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irTypeAtIndex = irExpression->getIRType()->getStructIRType()->getIRTypeByIndex(i);
        auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getStructIRType()->getType(), tupleAllocation, i);
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irTypeAtIndex);
    }

    auto pointerToTuplePointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getType(), tupleRefAllocation, irExpression->getIRType()->getStructIndex());
    InstructionIRInjectorHelper::injectStore(tupleAllocation, pointerToTuplePointer, irBlock);
    auto pointerToCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getType(), tupleRefAllocation, irExpression->getIRType()->getCounterIndex());
    auto arc = InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
    InstructionIRInjectorHelper::injectStore(arc, pointerToCounterPointer, irBlock);

    if (irOperation->isOperandPointer()) {
        return tupleRefAllocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), tupleRefAllocation, irBlock, irExpression->getIRType());
}