//
// Created by Johny Georges on 2025-03-24.
//

#include "string-ir-dref-expression-injector-strategy.h"

llvm::Value* StringIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irPointerValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), irPointerValue);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), loadedPointer);
}