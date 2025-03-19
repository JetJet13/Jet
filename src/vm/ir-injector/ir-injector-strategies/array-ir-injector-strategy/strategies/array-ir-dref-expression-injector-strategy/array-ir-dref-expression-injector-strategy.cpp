//
// Created by Johny Georges on 2025-03-19.
//

#include "array-ir-dref-expression-injector-strategy.h"

llvm::Value* ArrayIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    // todo: this strategy doesn't do a full copy yet. It only copies the array pointer.
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), irValue);
}