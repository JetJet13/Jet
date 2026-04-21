//
// Created by Johny Georges on 2025-11-24.
//

#include "llvm/Support/raw_ostream.h"
#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../debug-ir-injector-helper/debug-ir-injector-helper.h"

void FreeIRInjectorHelper::freeFunctionBlockNodes(IRBlockNode* functionBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto index = 0;
    for (auto childBlock : *functionBlock->getAllSuccessors()) {
        if (childBlock->hasNodesToFree() && !childBlock->isOneOf({ IR_BASIC_BT })) {
            childBlock->setInsertionPointBeforeLastInstruction();
            FreeIRInjectorHelper::freeNodes(
                    childBlock,
                    childBlock->getAllNodesToFree(),
                    irInjector,
                    irModule,
                    scope
            );
            DebugIRInjectorHelper::injectControlFlowEnterLog(childBlock, index, irInjector, irModule);
            DebugIRInjectorHelper::injectControlFlowExitLog(childBlock, index, irInjector, irModule);
        }
        index++;
    }

    FreeIRInjectorHelper::freeNodes(
            functionBlock,
            functionBlock->getAllNodesToFree(),
            irInjector,
            irModule,
            scope
    );
}

void FreeIRInjectorHelper::freeNodes(IRBlockNode* irBlockNode, std::vector<IRNodeToFree*>* nodesToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto allBlocksThatReturn = irBlockNode->getAllSuccessorsThatReturn();
    for (auto block : allBlocksThatReturn) {
        block->setInsertionPointBeforeLastInstruction();
        for (auto irNodeToFree : *nodesToFree) {
            if (!irNodeToFree->comesBefore(block)) {
                continue;
            } else if (irNodeToFree->getIRNode()->isExpression()) {
                FreeIRInjectorHelper::freeExpression(block->getLastSuccessorOrSelf(), (IRExpressionNode*)irNodeToFree->getIRNode(), irInjector, irModule, scope);
            } else {
                FreeIRInjectorHelper::freeVariable(block->getLastSuccessorOrSelf(), (IRVariableDeclarationNode*)irNodeToFree->getIRNode(), irInjector, irModule, scope);
            }
        }
    }
    if (allBlocksThatReturn.empty()) {
        irBlockNode->setInsertionPointBeforeLastInstruction();
        for (auto irNodeToFree : *nodesToFree) {
            if (irNodeToFree->getIRNode()->isExpression()) {
                FreeIRInjectorHelper::freeExpression(irBlockNode->getLastSuccessorOrSelf(), (IRExpressionNode*)irNodeToFree->getIRNode(), irInjector, irModule, scope);
            } else {
                FreeIRInjectorHelper::freeVariable(irBlockNode->getLastSuccessorOrSelf(), (IRVariableDeclarationNode*)irNodeToFree->getIRNode(), irInjector, irModule, scope);
            }
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
    auto allBlocksThatReturn = irBlockNode->getAllSuccessorsThatReturn();
    for (auto block : allBlocksThatReturn) {
        block->setInsertionPointBeforeLastInstruction();
        for (auto parameter : *functionParameterList->getParameters()) {
            if (parameter->getParameterType()->getIRType()->getUnderlyingType()->isInvocableType()) {
                DebugIRInjectorHelper::injectLog(irBlockNode, "[free-invocable-parameter] " + parameter->getParameterType()->getName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
                block->getBuilder()->get()->CreateCall(
                        irModule->getFreeInvocableFunction(),
                        {
                                scope->find(parameter->getParameterType()->getName()).value()->getValue(),
                        }
                );
            } else if (parameter->needsToBeFreed()) {
                auto typeValue = irInjector->inject(block, parameter->getParameterType()->getIRType()->clone());
                auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(
                        parameter->getParameterType()->getIRType()->getValue()->getAllocatedType(), typeValue,
                        block
                );
                DebugIRInjectorHelper::injectLog(irBlockNode, "[free-parameter] " + parameter->getParameterType()->getName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
                block->getBuilder()->get()->CreateCall(
                        irModule->getFreeValueFunction(),
                        {
                                scope->find(parameter->getParameterType()->getName()).value()->getValue(),
                                loadedTypeValue
                        }
                );
            }
        }
    }
}