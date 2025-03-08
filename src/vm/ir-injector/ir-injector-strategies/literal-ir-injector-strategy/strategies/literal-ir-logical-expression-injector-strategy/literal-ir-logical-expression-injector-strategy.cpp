//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-logical-expression-injector-strategy.h"

llvm::Value* LiteralIRLogicalExpressionInjectorStrategy::inject(IRLogicalExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), irOperationType, irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), irOperationType, irModule, scope);
    return irBlock->getBuilder()->get()->CreateBinOp(irExpression->getValue()->getOpcode(), irLeftNodeValue, irRightNodeValue);
}