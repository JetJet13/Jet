//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-binary-comparison-expression-injector-strategy.h"

llvm::Value* LiteralIRBinaryComparisonExpressionInjectorStrategy::inject(IRBinaryComparisonExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), IR_OPERAND_VALUE_OP, irModule, scope);
    return irBlock->getBuilder()->get()->CreateCmp(irExpression->getValue()->getPredicate(), irLeftNodeValue, irRightNodeValue);
}