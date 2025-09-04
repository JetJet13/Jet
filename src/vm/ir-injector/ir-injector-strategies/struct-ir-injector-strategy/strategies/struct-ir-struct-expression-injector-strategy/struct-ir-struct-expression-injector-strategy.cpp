//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-struct-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRStructExpressionInjectorStrategy::inject(IRStructExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto structExpressionAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto numElements = irExpression->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRType()->getType(), structExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, irOperationType, irModule, scope);
        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
    }
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), structExpressionAllocation);
}