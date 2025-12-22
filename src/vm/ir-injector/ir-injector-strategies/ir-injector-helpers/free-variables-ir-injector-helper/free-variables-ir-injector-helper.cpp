//
// Created by Johny Georges on 2025-11-24.
//

#include "llvm/Support/raw_ostream.h"
#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-lambda-type.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../debug-ir-injector-helper/debug-ir-injector-helper.h"

void FreeIRInjectorHelper::freeFunctionBlockVariables(IRBlockNode* functionBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto index = 0;
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
            DebugIRInjectorHelper::injectControlFlowEnterLog(childBlock, index, irInjector, irModule);
            DebugIRInjectorHelper::injectControlFlowExitLog(childBlock, index, irInjector, irModule);
        }
        index++;
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
//    for (auto variableToFree : *variablesToFree) {
//        auto typeValue = irInjector->inject(irBlockNode, variableToFree->getAllocatedIRType());
//        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variableToFree->getIRValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
//        irBlockNode->getBuilder()->get()->CreateCall(
//                irModule->getPrintDebugStringFunction(),
//                {
//                    irInjector->injectRawString(irBlockNode, "[free-var] " + variableToFree->getVariableName() + " - " + irBlockNode->getBlock()->getParent()->getName().str() + "\n")
//                }
//        );
//        irBlockNode->getBuilder()->get()->CreateCall(
//            irModule->getFreeValueFunction(),
//            {
//                variableToFree->getValue(),
//                loadedTypeValue
//            }
//        );
//    }
}

void FreeIRInjectorHelper::freeBlockLambdaVariables(IRBlockNode* irBlockNode, std::vector<IRVariableDeclarationNode*>* lambdaVariablesToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
//    for (auto lambdaVariableToFree : *lambdaVariablesToFree) {
//        irBlockNode->getBuilder()->get()->CreateCall(
//            irModule->getFreeLambdaFunction(),
//            {
//                lambdaVariableToFree->getValue()
//            }
//        );
//    }
}

void FreeIRInjectorHelper::freeBlockExpressions(IRBlockNode* irBlockNode, std::vector<IRExpressionNode*>* expressionsToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
//    for (auto expressionToFree : *expressionsToFree) {
//        auto typeValue = irInjector->inject(irBlockNode, expressionToFree->getIRType());
//        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(expressionToFree->getIRType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
//        std::string name = std::to_string(expressionToFree->getStartPosition()->getLine())
//                + ":"
//                + std::to_string(expressionToFree->getStartPosition()->getColumn());
//        irBlockNode->getBuilder()->get()->CreateCall(
//            irModule->getPrintDebugStringFunction(),
//            {
//                irInjector->injectRawString(irBlockNode, "[free-exp] "  + name + " - " + irBlockNode->getBlock()->getParent()->getName().str() + "\n")
//            }
//        );
//        irBlockNode->getBuilder()->get()->CreateCall(
//                irModule->getFreeValueFunction(),
//                {
//                    expressionToFree->getSourceAllocation().has_value()
//                    ? expressionToFree->getSourceAllocation().value()->getValue()
//                    : expressionToFree->getValue(),
//                    loadedTypeValue
//                }
//        );
//    }
}

void FreeIRInjectorHelper::freeFunctionParameters(IRBlockNode* irBlockNode, IRFunctionParameterListNode* functionParameterList, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
//    auto finalBlock = irBlockNode->getLastSuccessorOrSelf();
//    finalBlock->setInsertionPointBeforeLastInstruction();
//    for (auto parameter : *functionParameterList->getParameters()) {
//        if (parameter->needsToBeFreed()) {
//            auto typeValue = irInjector->inject(finalBlock, parameter->getParameterType()->getIRType());
//            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(
//                    parameter->getParameterType()->getIRType()->getValue()->getAllocatedType(), typeValue,
//                    finalBlock
//            );
//            finalBlock->getBuilder()->get()->CreateCall(
//                    irModule->getFreeValueFunction(),
//                    {
//                        scope->find(parameter->getParameterType()->getName()).value()->getValue(),
//                        loadedTypeValue
//                    }
//            );
//        }
//    }
}