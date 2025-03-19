//
// Created by Johny Georges on 2025-03-19.
//

#include "literal-ir-dref-expression-injector-strategy.h"

llvm::Value* LiteralIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), irValue);
}