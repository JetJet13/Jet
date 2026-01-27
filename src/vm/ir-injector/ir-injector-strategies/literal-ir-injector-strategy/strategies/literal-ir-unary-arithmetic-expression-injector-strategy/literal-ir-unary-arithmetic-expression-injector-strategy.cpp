//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-unary-arithmetic-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../../shared/utils/logger/logger.h"

llvm::Value* LiteralIRUnaryArithmeticExpressionInjectorStrategy::inject(IRUnaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto result = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(result->getType());
        InstructionIRInjectorHelper::injectStore(result, allocation, irBlock);
        return allocation;
    }
    return result;
}