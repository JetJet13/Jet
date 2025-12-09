//
// Created by Johny Georges on 2025-11-24.
//

#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-lambda-type.h"
#include "../../../../../shared/utils/logger/logger.h"

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
    FreeIRInjectorHelper::freeBlockLambdaVariables(
            finalBlock,
            functionBlock->getLambdaVariablesToFree(),
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

void FreeIRInjectorHelper::freeBlockLambdaVariables(IRBlockNode* irBlockNode, std::vector<IRVariableDeclarationNode*>* lambdaVariablesToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    for (auto lambdaVariableToFree : *lambdaVariablesToFree) {
        auto irLambdaType = (IRLambdaType*)lambdaVariableToFree->getIRExpression()->getIRType();
        auto pointerToLambdaScope = irBlockNode->getBuilder()->get()->CreateStructGEP(irLambdaType->getLambdaVariableType()->getType(), lambdaVariableToFree->getValue(), irLambdaType->getLambdaVariableType()->getFunctionScopeArgumentIndex());
        auto loadedLambdaScope = InstructionIRInjectorHelper::injectLoad(irLambdaType->getLambdaVariableType()->getFunctionScopeArgumentType(), pointerToLambdaScope, irBlockNode);
        auto pointerToCleanupFunction = irBlockNode->getBuilder()->get()->CreateStructGEP(irLambdaType->getLambdaVariableType()->getType(), lambdaVariableToFree->getValue(), irLambdaType->getLambdaVariableType()->getFunctionCleanupIndex());
        auto loadedCleanupFunction = InstructionIRInjectorHelper::injectLoad(irLambdaType->getLambdaVariableType()->getFunctionCleanupType(), pointerToCleanupFunction, irBlockNode);
        irBlockNode->getBuilder()->get()->CreateCall(
            irLambdaType->getLambdaVariableType()->getCleanupFunctionType(),
            loadedCleanupFunction,
            {
                loadedLambdaScope
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