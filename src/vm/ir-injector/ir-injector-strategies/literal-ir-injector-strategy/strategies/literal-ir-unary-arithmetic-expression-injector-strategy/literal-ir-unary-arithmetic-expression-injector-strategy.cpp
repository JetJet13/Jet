//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-arithmetic-expression-injector-strategy.h"

llvm::Value* LiteralIRUnaryArithmeticExpressionInjectorStrategy::inject(IRUnaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto result = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperationType == IR_OPERAND_POINTER_OP) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(result->getType());
        irBlock->getBuilder()->get()->CreateStore(result, allocation);
        return allocation;
    }
    return result;
}