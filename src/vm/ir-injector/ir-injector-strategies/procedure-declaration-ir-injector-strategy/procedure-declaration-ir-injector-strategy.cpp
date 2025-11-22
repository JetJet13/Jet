//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

void ProcedureDeclarationIRInjectorStrategy::inject(IRProcedureDeclarationNode* irProcedureDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irProcedureDeclaration->getBlock(), irModule, irProcedureDeclaration->getScope());
    if (!irProcedureDeclaration->getBlock()->hasReturnStatement()) {
        irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf()->addVoidReturn();
    }

    auto finalBlock = irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf();
    finalBlock->setInsertionPointBeforeReturn();
    for (auto variableToFree : *irProcedureDeclaration->getBlock()->getAllVariablesToFree()) {
        auto typeValue = irInjector->inject(finalBlock, variableToFree->getAllocatedIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variableToFree->getIRValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, finalBlock);
        finalBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction()->getFunctionType(),
                irModule->getFreeValueFunction(),
                {
                    variableToFree->getValue(),
                    loadedTypeValue
                }
        );
    }
}