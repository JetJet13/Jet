//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ProcedureDeclarationIRInjectorStrategy::inject(IRProcedureDeclarationNode* irProcedureDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irProcedureDeclaration->getBlock(), irModule, irProcedureDeclaration->getScope());
    for (auto instructionToFree: scope->getAllInstructionsToFree()) {
//        auto typeValue = irInjector->inject(irProcedureDeclaration->getBlock(), instructionToFree->getIRType()->getUnderlyingType());
//        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(
//                instructionToFree->getIRType()->getUnderlyingType()->getValue()->getAllocatedType(),
//                typeValue, irProcedureDeclaration->getBlock());
//        irProcedureDeclaration->getBlock()->getBuilder()->get()->CreateCall(
//                irModule->getFreeValueFunction()->getFunctionType(),
//                irModule->getFreeValueFunction(),
//                {
//                    instructionToFree->getValue(),
//                    loadedTypeValue
//                }
//        );
    }
    if (!irProcedureDeclaration->getBlock()->hasReturnStatement()) {
        irProcedureDeclaration->getBlock()->getLastSuccessorOrSelf()->addVoidReturn();
    }
}