//
// Created by Johny Georges on 2025-11-24.
//

#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void FreeIRInjectorHelper::freeBlockVariables(IRBlockNode* irBlockNode, std::vector<IRVariableDeclarationNode*>* variablesToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    for (auto variableToFree : *variablesToFree) {
        auto typeValue = irInjector->inject(irBlockNode, variableToFree->getAllocatedIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variableToFree->getIRValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
        irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getFreeValueFunction()->getFunctionType(),
            irModule->getFreeValueFunction(),
            {
                variableToFree->getValue(),
                loadedTypeValue
            }
        );
    }
}