//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

void ProcedureDeclarationIRInjectorStrategy::inject(IRProcedureDeclarationNode* irProcedureDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irProcedureDeclaration->getBlock(), irModule);
    if (!irProcedureDeclaration->getBlock()->hasReturnStatement()) {
        irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf()->addVoidReturn();
    }

    FreeIRInjectorHelper::freeFunctionBlockNodes(irProcedureDeclaration->getBlock(), irInjector, irModule, irProcedureDeclaration->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getParameters(), irInjector, irModule, irProcedureDeclaration->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getName(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getName(), irInjector, irModule);
}