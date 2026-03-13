//
// Created by Johny Georges on 2025-11-24.
//

#include "llvm/Support/raw_ostream.h"
#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../debug-ir-injector-helper/debug-ir-injector-helper.h"

void FreeIRInjectorHelper::freeFunctionBlockNodes(IRBlockNode* functionBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto index = 0;
    for (auto childBlock : *functionBlock->getAllSuccessors()) {
        if (childBlock->hasNodesToFree() && !childBlock->isOneOf({IR_BASIC_BT })) {
            childBlock->setInsertionPointBeforeLastInstruction();
            FreeIRInjectorHelper::freeNodes(
                    childBlock,
                    childBlock->getNodesToFree(),
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
    FreeIRInjectorHelper::freeNodes(
            finalBlock,
            functionBlock->getNodesToFree(),
            irInjector,
            irModule,
            scope
    );
}

void FreeIRInjectorHelper::freeNodes(IRBlockNode* irBlockNode, std::vector<IRNode*>* nodesToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    for (auto node : *nodesToFree) {
        if (node->isExpression()) {
            FreeIRInjectorHelper::freeExpression(irBlockNode, (IRExpressionNode*)node, irInjector, irModule, scope);
        } else {
            FreeIRInjectorHelper::freeVariable(irBlockNode, (IRVariableDeclarationNode*)node, irInjector, irModule, scope);
        }
    }
}

void FreeIRInjectorHelper::freeVariable(IRBlockNode* irBlockNode, IRVariableDeclarationNode* variableToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (variableToFree->getAllocatedIRType()->isInvocableType()) {
        DebugIRInjectorHelper::injectLog(irBlockNode, "[free-invocable-var] " + variableToFree->getVariableName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
        irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getFreeInvocableFunction(),
            {
                variableToFree->getValue(),
            }
        );
        return;
    }
    auto typeValue = irInjector->inject(irBlockNode, variableToFree->getAllocatedIRType()->clone());
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variableToFree->getIRValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
    DebugIRInjectorHelper::injectLog(irBlockNode, "[free-var] " + variableToFree->getVariableName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
    irBlockNode->getBuilder()->get()->CreateCall(
        irModule->getFreeValueFunction(),
        {
            variableToFree->getValue(),
            loadedTypeValue
        }
    );
}

void FreeIRInjectorHelper::freeExpression(IRBlockNode* irBlockNode, IRExpressionNode* expressionToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    std::string name = std::to_string(expressionToFree->getStartPosition()->getLine())
                       + ":"
                       + std::to_string(expressionToFree->getStartPosition()->getColumn());
    if (expressionToFree->getIRType()->isInvocableType()) {
        DebugIRInjectorHelper::injectLog(irBlockNode, "[free-invocable-exp] "  + name + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
        irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeInvocableFunction(), { expressionToFree->getValue() });
        return;
    }
    auto typeValue = irInjector->inject(irBlockNode, expressionToFree->getIRType()->clone());
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(expressionToFree->getIRType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
    auto value = expressionToFree->getSourceAllocation().has_value()
                 ? expressionToFree->getSourceAllocation().value()->getValue()
                 : expressionToFree->getValue();
    std::string log = "[free-exp] "  + name + " - " + irBlockNode->getBlock()->getParent()->getName().str();
    DebugIRInjectorHelper::injectLog(irBlockNode, log, irInjector, irModule);

    if (!value->getType()->isPointerTy()) {
        auto alloc = irBlockNode->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, alloc, irBlockNode, expressionToFree->getIRType());
        irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeValueFunction(), { alloc, loadedTypeValue });
        return;
    }
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeValueFunction(), { value, loadedTypeValue });
}

void FreeIRInjectorHelper::freeFunctionParameters(IRBlockNode* irBlockNode, IRFunctionParameterListNode* functionParameterList, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto finalBlock = irBlockNode->getLastSuccessorOrSelf();
    finalBlock->setInsertionPointBeforeLastInstruction();
    for (auto parameter : *functionParameterList->getParameters()) {
        if (parameter->getParameterType()->getIRType()->getUnderlyingType()->isInvocableType()) {
            DebugIRInjectorHelper::injectLog(irBlockNode, "[free-invocable-parameter] " + parameter->getParameterType()->getName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
            finalBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeInvocableFunction(),
                {
                    scope->find(parameter->getParameterType()->getName()).value()->getValue(),
                }
            );
        } else if (parameter->needsToBeFreed()) {
            auto typeValue = irInjector->inject(finalBlock, parameter->getParameterType()->getIRType()->clone());
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(
                    parameter->getParameterType()->getIRType()->getValue()->getAllocatedType(), typeValue,
                    finalBlock
            );
            DebugIRInjectorHelper::injectLog(irBlockNode, "[free-parameter] " + parameter->getParameterType()->getName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
            finalBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                {
                    scope->find(parameter->getParameterType()->getName()).value()->getValue(),
                    loadedTypeValue
                }
            );
        }
    }
}