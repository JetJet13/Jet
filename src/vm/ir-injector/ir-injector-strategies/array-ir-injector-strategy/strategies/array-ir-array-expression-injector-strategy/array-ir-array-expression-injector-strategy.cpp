//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-array-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* ArrayIRArrayExpressionInjectorStrategy::inject(IRArrayExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    irBlock->getBuilder()->get()->Insert(irExpression->getSourceAggregateAllocation()->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceAggregateAllocation()->getAllocatedType(),
                                                                       irExpression->getSourceAggregateAllocation()->getValue(), { zeroIndex, irIndex });
        auto irExpressionValue = irInjector->inject(irBlock, elementExpression, irOperationType, irModule, scope);
        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
    }

    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRType(), numElements,
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}