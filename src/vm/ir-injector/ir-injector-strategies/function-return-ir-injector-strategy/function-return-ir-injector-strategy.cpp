//
// Created by Johny Georges on 2024-08-15.
//

#include "function-return-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void FunctionReturnIRInjectorStrategy::inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto returnValue = irInjector->inject(irBlock, irFunctionReturnExpression->getReturnExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    for (auto instructionToFree: scope->getAllInstructionsToFree()) {
        auto typeValue = irInjector->inject(irBlock, instructionToFree->getIRType()->getSourceType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(instructionToFree->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlock);
            irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction()->getFunctionType(),
                irModule->getFreeValueFunction(),
                {
                    instructionToFree->getValue(),
                    loadedTypeValue
                }
        );
    }
    irBlock->getBuilder()->get()->CreateRet(returnValue);
}