//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"

void ProcedureDeclarationIRInjectorStrategy::inject(IRProcedureDeclarationNode* irProcedureDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irProcedureDeclaration->getBlock(), irModule, irProcedureDeclaration->getScope());
    if (!irProcedureDeclaration->getBlock()->hasReturnStatement()) {
        irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf()->addVoidReturn();
    }

    for (auto childBlock : *irProcedureDeclaration->getBlock()->getAllSuccessors()) {
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

    auto finalBlock = irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf();
    finalBlock->setInsertionPointBeforeLastInstruction();
    FreeIRInjectorHelper::freeBlockVariables(
            finalBlock,
            irProcedureDeclaration->getBlock()->getVariablesToFree(),
            irInjector,
            irModule,
            scope
    );
}