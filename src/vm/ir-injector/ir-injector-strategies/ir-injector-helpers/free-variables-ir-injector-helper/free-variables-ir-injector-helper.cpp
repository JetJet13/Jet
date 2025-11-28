//
// Created by Johny Georges on 2025-11-24.
//

#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void FreeIRInjectorHelper::freeFunctionBlockVariables(IRBlockNode* functionBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    for (auto childBlock : *functionBlock->getAllSuccessors()) {
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

    auto finalBlock = functionBlock->getLastSuccessorOrSelf();
    finalBlock->setInsertionPointBeforeLastInstruction();
    FreeIRInjectorHelper::freeBlockVariables(
            finalBlock,
            functionBlock->getVariablesToFree(),
            irInjector,
            irModule,
            scope
    );
}

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

void FreeIRInjectorHelper::freeFunctionParameters(IRBlockNode* irBlockNode, IRFunctionParameterListNode* functionParameterList, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto finalBlock = irBlockNode->getLastSuccessorOrSelf();
    finalBlock->setInsertionPointBeforeLastInstruction();
    for (auto parameter : *functionParameterList->getParameters()) {
        if (parameter->needsToBeFreed()) {
            auto typeValue = irInjector->inject(finalBlock, parameter->getParameterType()->getIRType());
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(
                    parameter->getParameterType()->getIRType()->getValue()->getAllocatedType(), typeValue,
                    finalBlock);
            finalBlock->getBuilder()->get()->CreateCall(
                    irModule->getFreeValueFunction()->getFunctionType(),
                    irModule->getFreeValueFunction(),
                    {
                        scope->find(parameter->getParameterType()->getName()).value()->getValue(),
                        loadedTypeValue
                    }
            );
        }
    }
}