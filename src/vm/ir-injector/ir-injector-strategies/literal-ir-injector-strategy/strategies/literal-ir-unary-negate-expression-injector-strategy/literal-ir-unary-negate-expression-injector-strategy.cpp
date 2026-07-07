//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-negate-expression-injector-strategy.h"

llvm::Value* LiteralIRUnaryNegateExpressionInjectorStrategy::inject(std::shared_ptr<IRUnaryNegateExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto value = irInjector->inject(irBlock, irExpression->getIRExpression(), std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
    if (value->getType()->isIntegerTy(1)) {
        return irBlock->getBuilder()->get()->CreateXor(value, irBlock->getBuilder()->get()->getTrue());
    }
    return irBlock->getBuilder()->get()->getFalse();
}