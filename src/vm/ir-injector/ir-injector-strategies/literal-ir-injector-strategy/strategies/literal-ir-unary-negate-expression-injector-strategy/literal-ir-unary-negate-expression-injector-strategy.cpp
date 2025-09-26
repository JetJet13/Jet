//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-negate-expression-injector-strategy.h"

llvm::Value* LiteralIRUnaryNegateExpressionInjectorStrategy::inject(IRUnaryNegateExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}