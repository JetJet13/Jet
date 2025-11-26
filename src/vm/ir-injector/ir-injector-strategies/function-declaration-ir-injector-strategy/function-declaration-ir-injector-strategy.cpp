//
// Created by Johny Georges on 2025-01-11.
//

#include "function-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"

void FunctionDeclarationIRInjectorStrategy::inject(IRFunctionDeclarationNode* irFunctionDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    for (auto statement: *irFunctionDeclaration->getBlock()->getBody()) {
        irInjector->inject(irFunctionDeclaration->getBlock(), statement, irModule, irFunctionDeclaration->getScope());
    }

    for (auto childBlock : *irFunctionDeclaration->getBlock()->getAllSuccessors()) {
        if (childBlock->hasVariablesToFree() && !childBlock->is(IR_BASIC_BT)) {
            childBlock->setInsertionPointBeforeLastInstruction();
            FreeIRInjectorHelper::freeBlockVariables(
                    childBlock,
                    childBlock->getVariablesToFree(),
                    irInjector,
                    irModule,
                    scope
            );
        }
    }

    auto finalBlock = irFunctionDeclaration->getBlock()->getLastSuccessorOrSelf();
    finalBlock->setInsertionPointBeforeLastInstruction();
    FreeIRInjectorHelper::freeBlockVariables(
            finalBlock,
            irFunctionDeclaration->getBlock()->getVariablesToFree(),
            irInjector,
            irModule,
            scope
    );
}