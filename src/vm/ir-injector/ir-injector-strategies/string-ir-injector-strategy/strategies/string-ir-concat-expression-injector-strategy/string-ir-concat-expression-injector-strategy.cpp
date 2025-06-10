//
// Created by Johny Georges on 2025-06-09.
//

#include "string-ir-concat-expression-injector-strategy.h"

llvm::Value* StringIRConcatExpressionInjectorStrategy::inject(IRConcatExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irExpression->getLeftNode(), IR_OPERAND_OP, irModule, scope);
    irInjector->inject(irBlock, irExpression->getRightNode(), IR_OPERAND_OP, irModule, scope);
    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}