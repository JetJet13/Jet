//
// Created by Johny Georges on 2025-01-11.
//

#include "function-declaration-ir-injector-strategy.h"

void FunctionDeclarationIRInjectorStrategy::inject(IRFunctionDeclarationNode* irFunctionDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    for (auto statement : *irFunctionDeclaration->getBlock()->getBody()) {
        irInjector->inject(irFunctionDeclaration->getBlock(), statement, irModule, irFunctionDeclaration->getScope());
    }
}