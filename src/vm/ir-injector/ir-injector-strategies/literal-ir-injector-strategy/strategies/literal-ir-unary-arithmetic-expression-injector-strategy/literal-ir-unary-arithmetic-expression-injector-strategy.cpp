//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-arithmetic-expression-injector-strategy.h"

llvm::Value* LiteralIRUnaryArithmeticExpressionInjectorStrategy::inject(IRUnaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}