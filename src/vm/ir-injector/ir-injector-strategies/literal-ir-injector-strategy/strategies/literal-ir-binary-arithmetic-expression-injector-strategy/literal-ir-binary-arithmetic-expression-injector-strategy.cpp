//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-binary-arithmetic-expression-injector-strategy.h"

llvm::Value* LiteralIRBinaryArithmeticExpressionInjectorStrategy::inject(IRBinaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), irOperationType, irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), irOperationType, irModule, scope);
    return irBlock->getBuilder()->get()->CreateBinOp(irExpression->getValue()->getOpcode(), irLeftNodeValue, irRightNodeValue);
}