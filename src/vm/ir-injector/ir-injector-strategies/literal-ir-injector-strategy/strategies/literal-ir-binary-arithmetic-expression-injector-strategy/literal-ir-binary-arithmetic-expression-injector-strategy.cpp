//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-binary-arithmetic-expression-injector-strategy.h"

llvm::Value* LiteralIRBinaryArithmeticExpressionInjectorStrategy::inject(IRBinaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto result = irBlock->getBuilder()->get()->CreateBinOp(irExpression->getValue()->getOpcode(), irLeftNodeValue, irRightNodeValue);
    if (irOperationType == IR_OPERAND_POINTER_OP) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(result->getType());
        irBlock->getBuilder()->get()->CreateStore(result, allocation);
        return allocation;
    }
    return result;
}