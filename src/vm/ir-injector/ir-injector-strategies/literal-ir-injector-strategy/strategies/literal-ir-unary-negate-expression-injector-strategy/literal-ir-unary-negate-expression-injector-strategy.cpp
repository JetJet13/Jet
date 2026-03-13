//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-negate-expression-injector-strategy.h"

llvm::Value* LiteralIRUnaryNegateExpressionInjectorStrategy::inject(IRUnaryNegateExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto value = irInjector->inject(irBlock, irExpression->getIRExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    if (value->getType()->isIntegerTy(1)) {
        return irBlock->getBuilder()->get()->CreateXor(value, irBlock->getBuilder()->get()->getTrue());
    }
    return irBlock->getBuilder()->get()->getFalse();
}