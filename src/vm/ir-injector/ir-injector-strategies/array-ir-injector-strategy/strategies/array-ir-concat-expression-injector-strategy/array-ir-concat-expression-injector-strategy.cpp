//
// Created by Johny Georges on 2025-06-09.
//

#include "array-ir-concat-expression-injector-strategy.h"

llvm::Value* ArrayIRConcatExpressionInjectorStrategy::inject(IRConcatExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irExpression->getLeftNode(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    irInjector->inject(irBlock, irExpression->getRightNode(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}