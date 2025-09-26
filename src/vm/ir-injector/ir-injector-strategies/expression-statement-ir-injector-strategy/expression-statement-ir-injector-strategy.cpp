//
// Created by Johny Georges on 2025-06-16.
//

#include "expression-statement-ir-injector-strategy.h"

void ExpressionStatementIRInjectorStrategy::inject(IRExpressionStatementNode* irExpressionStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irExpressionStatement->getExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
}