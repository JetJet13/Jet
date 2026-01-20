//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-logical-expression-injector-strategy.h"

llvm::Value* LiteralIRLogicalExpressionInjectorStrategy::inject(IRLogicalExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), (new IROperation(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), (new IROperation(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    return irBlock->getBuilder()->get()->CreateBinOp(irExpression->getValue()->getOpcode(), irLeftNodeValue, irRightNodeValue);
}