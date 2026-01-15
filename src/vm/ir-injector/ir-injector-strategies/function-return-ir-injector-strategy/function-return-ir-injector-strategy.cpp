//
// Created by Johny Georges on 2024-08-15.
//

#include "function-return-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"

void FunctionReturnIRInjectorStrategy::inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    Logger::log("HELLO!");
    auto returnValue = irInjector->inject(irBlock, irFunctionReturnExpression->getReturnExpression(), new IROperation(IR_FUNCTION_RETURN_OP), irModule, scope);
    Logger::log("RETURN VALUE", returnValue);
    irBlock->addReturnExpression(irFunctionReturnExpression);
    irBlock->getBuilder()->get()->CreateRet(returnValue);
}