//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-struct-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRStructExpressionInjectorStrategy::inject(IRStructExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto structExpressionAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto numElements = irExpression->size();
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getType(), structExpressionAllocation, i);
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, irOperation, irModule, scope);
        InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irExpressionAtIndex->getIRType());
    }
    if (irOperation->isOperandPointer()) {
        return structExpressionAllocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), structExpressionAllocation, irBlock);
}