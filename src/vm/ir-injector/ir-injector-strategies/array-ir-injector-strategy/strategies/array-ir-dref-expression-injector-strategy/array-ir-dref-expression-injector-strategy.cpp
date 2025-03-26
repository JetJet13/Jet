//
// Created by Johny Georges on 2025-03-19.
//

#include "array-ir-dref-expression-injector-strategy.h"

llvm::Value* ArrayIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irPointerValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), irPointerValue);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), loadedPointer);
}