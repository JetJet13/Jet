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
            FreeIRInjectorHelper::freeBlockExpressions(
                    childBlock,
                    childBlock->getExpressionsToFree(),
                    irInjector,
                    irModule,
                    scope
            );
            FreeIRInjectorHelper::refCheckVariables(
                    childBlock,
                    childBlock->getVariablesToRefCheck(),
                    irInjector,
                    irModule,
                    scope
            );
            FreeIRInjectorHelper::refCheckExpressions(
                    childBlock,
                    childBlock->getExpressionsToRefCheck(),
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
    FreeIRInjectorHelper::freeBlockExpressions(
            finalBlock,
            functionBlock->getExpressionsToFree(),
            irInjector,
            irModule,
            scope
    );
    FreeIRInjectorHelper::refCheckVariables(
            finalBlock,
            functionBlock->getVariablesToRefCheck(),
            irInjector,
            irModule,
            scope
    );
    FreeIRInjectorHelper::refCheckExpressions(
            finalBlock,
            functionBlock->getExpressionsToRefCheck(),
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

void FreeIRInjectorHelper::freeBlockExpressions(IRBlockNode* irBlockNode, std::vector<IRExpressionNode*>* expressionsToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    for (auto expressionToFree : *expressionsToFree) {
        auto typeValue = irInjector->inject(irBlockNode, expressionToFree->getIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(expressionToFree->getIRType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
        irBlockNode->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction()->getFunctionType(),
                irModule->getFreeValueFunction(),
                {
                    expressionToFree->getSourceAllocation().has_value()
                    ? expressionToFree->getSourceAllocation().value()->getValue()
                    : expressionToFree->getValue(),
                    loadedTypeValue
                }
        );
    }
}

void FreeIRInjectorHelper::refCheckVariables(IRBlockNode* irBlockNode, std::vector<IRVariableDeclarationNode*>* variablesToRefCheck, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    for (auto variableToRefCheck : *variablesToRefCheck) {
        auto typeValue = irInjector->inject(irBlockNode, variableToRefCheck->getAllocatedIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variableToRefCheck->getIRValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
        irBlockNode->getBuilder()->get()->CreateCall(
                irModule->getFreeRefFunction()->getFunctionType(),
                irModule->getFreeRefFunction(),
                {
                    variableToRefCheck->getValue(),
                    loadedTypeValue
                }
        );
    }
}

void FreeIRInjectorHelper::refCheckExpressions(IRBlockNode* irBlockNode, std::vector<IRExpressionNode*>* expressionsToRefCheck, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    for (auto expressionToRefCheck : *expressionsToRefCheck) {
        auto typeValue = irInjector->inject(irBlockNode, expressionToRefCheck->getIRType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(expressionToRefCheck->getIRType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
        irBlockNode->getBuilder()->get()->CreateCall(
                irModule->getFreeRefFunction()->getFunctionType(),
                irModule->getFreeRefFunction(),
                {
                    expressionToRefCheck->getSourceAllocation().has_value()
                    ? expressionToRefCheck->getSourceAllocation().value()->getValue()
                    : expressionToRefCheck->getValue(),
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
                    finalBlock
            );
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