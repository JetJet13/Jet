//
// Created by Johny Georges on 2025-06-09.
//

#include "array-ir-concat-expression-injector-strategy.h"

llvm::Value* ArrayIRConcatExpressionInjectorStrategy::inject(IRConcatExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irExpression->getLeftNode(), IR_OPERAND_OP, irModule, scope);
    irInjector->inject(irBlock, irExpression->getRightNode(), IR_OPERAND_OP, irModule, scope);
    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}