//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-array-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ArrayIRArrayExpressionInjectorStrategy::inject(IRArrayExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    InstructionIRInjectorHelper::inject(irExpression->getSourceAggregateAllocation(), irBlock);
    auto numElements = irExpression->size();
    for (int i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRType()->getElementType(),
                                                                       irExpression->getSourceAggregateAllocation()->getValue(), { irIndex });
        auto irExpressionValue = irInjector->inject(irBlock, elementExpression, irOperationType, irModule, scope);
        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
    }

    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRType(), numElements,
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}