//
// Created by Johny Georges on 2025-01-11.
//

#include "function-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

void FunctionDeclarationIRInjectorStrategy::inject(IRFunctionDeclarationNode* irFunctionDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irFunctionDeclaration->getBlock(), irModule, irFunctionDeclaration->getScope());
    FreeIRInjectorHelper::freeFunctionBlockVariables(irFunctionDeclaration->getBlock(), irInjector, irModule, irFunctionDeclaration->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irFunctionDeclaration->getBlock(), irFunctionDeclaration->getParameters(), irInjector, irModule, irFunctionDeclaration->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irFunctionDeclaration->getBlock(), irFunctionDeclaration->getName(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irFunctionDeclaration->getBlock(), irFunctionDeclaration->getName(), irInjector, irModule);
}