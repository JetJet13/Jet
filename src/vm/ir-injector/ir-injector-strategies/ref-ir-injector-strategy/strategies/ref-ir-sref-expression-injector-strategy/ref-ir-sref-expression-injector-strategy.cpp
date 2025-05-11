//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-sref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRSrefExpressionInjectorStrategy::inject(IRSrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    // todo: cleanup to work with ref type { ptr, ptr }
    auto pointerToPointerValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    auto loadedPointerToValue = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), pointerToPointerValue);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    irBlock->getBuilder()->get()->CreateStore(loadedPointerToValue, allocation);
    return allocation;
}