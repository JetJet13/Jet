//
// Created by Johny Georges on 2024-08-15.
//

#include "function-return-ir-injector-strategy.h"

void FunctionReturnIRInjectorStrategy::inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto returnValue = irInjector->inject(irBlock, irFunctionReturnExpression->getReturnExpression(), IR_OPERAND_OP, irModule, scope);
    irBlock->getBuilder()->get()->CreateRet(returnValue);
}