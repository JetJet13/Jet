//
// Created by Johny Georges on 2024-08-15.
//

#include "function-return-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"

void FunctionReturnIRInjectorStrategy::inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irFunctionReturnExpression->getReturnExpression()) {
        auto returnValue = irInjector->inject(irBlock, irFunctionReturnExpression->getReturnExpression().value(), new IROperation(IR_FUNCTION_RETURN_OP), irModule, scope);
        irBlock->getBuilder()->get()->CreateRet(returnValue);
    } else {
        irBlock->addVoidReturn();
    }
    irBlock->addReturnExpression(irFunctionReturnExpression);
}