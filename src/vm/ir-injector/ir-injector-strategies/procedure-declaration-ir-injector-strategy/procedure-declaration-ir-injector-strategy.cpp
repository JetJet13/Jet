//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"

void ProcedureDeclarationIRInjectorStrategy::inject(IRProcedureDeclarationNode* irProcedureDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    for (auto statement : *irProcedureDeclaration->getBlock()->getBody()) {
        irInjector->inject(irProcedureDeclaration->getBlock(), statement, irModule, irProcedureDeclaration->getScope());
    }
    for (auto variableToFree: *irProcedureDeclaration->getBlock()->getVariablesToFree()) {
        auto typeValue = irInjector->inject(irProcedureDeclaration->getBlock(), variableToFree->getAllocatedIRType());
        auto loadedTypeValue = irProcedureDeclaration->getBlock()->getBuilder()->get()->CreateLoad(
                variableToFree->getAllocatedIRType()->getValue()->getAllocatedType(), typeValue);
        irProcedureDeclaration->getBlock()->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction()->getFunctionType(),
                irModule->getFreeValueFunction(),
                {
                        variableToFree->getValue(),
                        loadedTypeValue
                }
        );
    }
    auto procedureReturn = irProcedureDeclaration->getBlock()->getBuilder()->get()->getInt32(0);
    irProcedureDeclaration->getBlock()->getBuilder()->get()->CreateRet(procedureReturn);
}