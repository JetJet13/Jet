//
// Created by Johny Georges on 2025-03-29.
//

#include "pointer-ir-sref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRSrefExpressionInjectorStrategy::inject(IRSrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto pointerToPointerValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    auto loadedPointerToValue = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), pointerToPointerValue);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    irBlock->getBuilder()->get()->CreateStore(loadedPointerToValue, allocation);
    return allocation;
}
