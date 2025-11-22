//
// Created by Johny Georges on 2025-01-11.
//

#include "function-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void FunctionDeclarationIRInjectorStrategy::inject(IRFunctionDeclarationNode* irFunctionDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    for (auto statement: *irFunctionDeclaration->getBlock()->getBody()) {
        irInjector->inject(irFunctionDeclaration->getBlock(), statement, irModule, irFunctionDeclaration->getScope());
    }

//    irFunctionDeclaration->getBlock()->setInsertionPointBeforeReturn();
//    for (auto variablesToFree : *irFunctionDeclaration->getBlock()->getVariablesToFree()) {
//        auto typeValue = irInjector->inject(irFunctionDeclaration->getBlock(), variablesToFree->getIRValue()->getIRType()->getSourceType());
//        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variablesToFree->getIRValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irFunctionDeclaration->getBlock());
//        irFunctionDeclaration->getBlock()->getBuilder()->get()->CreateCall(
//                irModule->getFreeValueFunction()->getFunctionType(),
//                irModule->getFreeValueFunction(),
//                {
//                    variablesToFree->getValue(),
//                    loadedTypeValue
//                }
//        );
//    }
}