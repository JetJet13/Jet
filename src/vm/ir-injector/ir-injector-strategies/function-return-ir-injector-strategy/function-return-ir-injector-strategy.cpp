//
// Created by Johny Georges on 2024-08-15.
//

#include "function-return-ir-injector-strategy.h"

void FunctionReturnIRInjectorStrategy::inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto returnValue = irInjector->inject(irBlock, irFunctionReturnExpression->getReturnExpression(), IR_FUNCTION_RETURN_OP, irModule, scope);
    for (auto variableToFree: *irBlock->getVariablesToFree()) {
        auto typeValue = irInjector->inject(irBlock, variableToFree->getAllocatedIRType());
        auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(
            variableToFree->getAllocatedIRType()->getValue()->getAllocatedType(), typeValue);
            irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction()->getFunctionType(),
                irModule->getFreeValueFunction(),
                {
                    variableToFree->getValue(),
                    loadedTypeValue
                }
        );
    }
    irBlock->getBuilder()->get()->CreateRet(returnValue);
}