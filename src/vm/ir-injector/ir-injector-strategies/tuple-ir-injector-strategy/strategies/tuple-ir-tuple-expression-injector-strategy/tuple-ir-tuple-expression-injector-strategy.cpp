//
// Created by Johny Georges on 2025-03-08.
//

#include "tuple-ir-tuple-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* TupleIRTupleExpressionInjectorStrategy::inject(IRTupleExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto tupleExpressionAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto numElements = irExpression->size();
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getType(), tupleExpressionAllocation, i);
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, irOperationType, irModule, scope);
        InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irExpression->getIRType());
//        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), tupleExpressionAllocation, irBlock);
//    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), tupleExpressionAllocation);
}