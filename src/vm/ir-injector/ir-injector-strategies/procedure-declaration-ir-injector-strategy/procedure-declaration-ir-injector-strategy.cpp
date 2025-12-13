//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

void ProcedureDeclarationIRInjectorStrategy::inject(IRProcedureDeclarationNode* irProcedureDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irProcedureDeclaration->getBlock(), irModule, irProcedureDeclaration->getScope());
    if (!irProcedureDeclaration->getBlock()->hasReturnStatement()) {
        irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf()->addVoidReturn();
    }

    FreeIRInjectorHelper::freeFunctionBlockVariables(irProcedureDeclaration->getBlock(), irInjector, irModule, irProcedureDeclaration->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getParameters(), irInjector, irModule, irProcedureDeclaration->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getName(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getName(), irInjector, irModule);
}