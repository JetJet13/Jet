//
// Created by Johny Georges on 2025-11-24.
//

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Dominators.h"
#include "free-variables-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../debug-ir-injector-helper/debug-ir-injector-helper.h"

void FreeIRInjectorHelper::freeFunctionBlockNodes(std::shared_ptr<IRBlockNode> functionBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto index = 0;
    for (auto nestedBlock : *functionBlock->getNestedBlocks()) {
        if ((functionBlock->hasNodesToFree() || nestedBlock->hasNodesToFree()) && nestedBlock->isAllowedToFreeNodes()) {
            FreeIRInjectorHelper::freeNestedBlockNodes(
                    nestedBlock,
                    irInjector,
                    irModule,
                    scope
            );
            DebugIRInjectorHelper::injectControlFlowEnterLog(nestedBlock, index, irInjector, irModule);
            DebugIRInjectorHelper::injectControlFlowExitLog(nestedBlock, index, irInjector, irModule);
        }
        index++;
    }

    FreeIRInjectorHelper::freeNodes(
            functionBlock,
            functionBlock->getNodesToFree(),
            irInjector,
            irModule,
            scope
    );
}

void FreeIRInjectorHelper::freeNodes(std::shared_ptr<IRBlockNode> irBlockNode, std::vector<std::shared_ptr<IRNodeToFree>>* nodesToFree, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto dominator = llvm::DominatorTree(*irBlockNode->getBlock()->getParent());
    auto allChildrenThatReturn = irBlockNode->getAllChildrenThatReturn();
    for (auto childBlock : allChildrenThatReturn) {
        childBlock->setInsertionPointBeforeLastInstruction();
        for (auto irNodeToFree : *nodesToFree) {
            if (!irNodeToFree->comesBefore(childBlock, &dominator)) {
                continue;
            } else if (irNodeToFree->getIRNode()->isExpression()) {
                FreeIRInjectorHelper::freeExpression(childBlock, std::dynamic_pointer_cast<IRExpressionNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
            } else {
                FreeIRInjectorHelper::freeVariable(childBlock, std::dynamic_pointer_cast<IRVariableDeclarationNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
            }
        }
    }
}

void FreeIRInjectorHelper::freeForInLoopSource(std::shared_ptr<IRBlockNode> forInEndBlock, std::shared_ptr<IRBlockNode> forInSetupBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    forInEndBlock->setInsertionPointBeforeLastInstruction();
    for (auto irNodeToFree : *forInSetupBlock->getNodesToFree()) {
        FreeIRInjectorHelper::freeExpression(forInEndBlock, std::dynamic_pointer_cast<IRExpressionNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
    }
}

void FreeIRInjectorHelper::freeNestedBlockNodes(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto dominator = llvm::DominatorTree(*irBlockNode->getBlock()->getParent());
    auto blockNodesToFree = irBlockNode->getNodesToFree();
    auto allNodesToFree = irBlockNode->getNestedParentsNodesToFree();
    allNodesToFree.insert(allNodesToFree.begin(), blockNodesToFree->begin(), blockNodesToFree->end());
    auto allChildrenThatReturn = irBlockNode->getAllChildrenThatReturn();
    for (auto childBlock : allChildrenThatReturn) {
        childBlock->setInsertionPointBeforeLastInstruction();
        for (auto irNodeToFree : allNodesToFree) {
            if (!irNodeToFree->comesBefore(childBlock, &dominator)) {
                continue;
            } else if (irNodeToFree->getIRNode()->isExpression()) {
                FreeIRInjectorHelper::freeExpression(childBlock, std::dynamic_pointer_cast<IRExpressionNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
            } else {
                FreeIRInjectorHelper::freeVariable(childBlock, std::dynamic_pointer_cast<IRVariableDeclarationNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
            }
        }
    }

    if (irBlockNode->hasNestedBlocks() && irBlockNode->allImmediateNestedBlocksReturn()) {
        return;
    }

    auto lastBlock = irBlockNode->getLastChildOrSelf();
    if (!blockNodesToFree->empty() && !lastBlock->hasReturnInstruction()) {
        lastBlock->setInsertionPointBeforeLastInstruction();
        for (auto irNodeToFree : *blockNodesToFree) {
            if (!irNodeToFree->comesBefore(lastBlock, &dominator)) {
                continue;
            } else if (irNodeToFree->getIRNode()->isExpression()) {
                FreeIRInjectorHelper::freeExpression(lastBlock, std::dynamic_pointer_cast<IRExpressionNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
            } else {
                FreeIRInjectorHelper::freeVariable(lastBlock, std::dynamic_pointer_cast<IRVariableDeclarationNode>(irNodeToFree->getIRNode()), irInjector, irModule, scope);
            }
        }
    }
}

void FreeIRInjectorHelper::freeVariable(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRVariableDeclarationNode> variableToFree, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
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
    auto typeValue = irInjector->inject(irBlockNode, variableToFree->getAllocatedIRType(), irModule);
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

void FreeIRInjectorHelper::freeExpression(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRExpressionNode> expressionToFree, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    std::string name = std::to_string(expressionToFree->getStartPosition()->getLine())
                       + ":"
                       + std::to_string(expressionToFree->getStartPosition()->getColumn());
    if (expressionToFree->getIRType()->getSourceType()->isInvocableType()) {
        DebugIRInjectorHelper::injectLog(irBlockNode, "[free-invocable-exp] "  + name + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
        auto invocableValue = expressionToFree->getValue();
        if (!invocableValue->getType()->isPointerTy()) {
            auto alloc = irBlockNode->getBuilder()->get()->CreateAlloca(invocableValue->getType());
            InstructionIRInjectorHelper::injectStore(invocableValue, alloc, irBlockNode, expressionToFree->getIRType()->getSourceType());
            irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeInvocableFunction(), { alloc });
            return;
        }
        irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeInvocableFunction(), { invocableValue });
        return;
    }
    auto typeValue = irInjector->inject(irBlockNode, expressionToFree->getIRType()->getSourceType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(expressionToFree->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlockNode);
    auto value = expressionToFree->getSourceAllocation().has_value()
                 ? expressionToFree->getSourceAllocation().value()->getValue()
                 : expressionToFree->getValue();
    std::string log = "[free-exp] "  + name + " - " + irBlockNode->getBlock()->getParent()->getName().str();
    DebugIRInjectorHelper::injectLog(irBlockNode, log, irInjector, irModule);

    if (!value->getType()->isPointerTy()) {
        auto alloc = irBlockNode->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, alloc, irBlockNode, expressionToFree->getIRType()->getSourceType());
        irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeValueFunction(), { alloc, loadedTypeValue });
        return;
    }
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getFreeValueFunction(), { value, loadedTypeValue });
}

void FreeIRInjectorHelper::freeFunctionParameters(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRFunctionParameterListNode> functionParameterList, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto allChildBlocksThatReturn = irBlockNode->getAllChildrenThatReturn();
    for (auto childBlock : allChildBlocksThatReturn) {
        childBlock->setInsertionPointBeforeLastInstruction();
        for (auto parameter : *functionParameterList->getParameters()) {
            if (parameter->getParameterType()->getIRType()->getUnderlyingType()->isInvocableType()) {
                DebugIRInjectorHelper::injectLog(irBlockNode, "[free-invocable-parameter] " + parameter->getParameterType()->getName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
                childBlock->getBuilder()->get()->CreateCall(
                        irModule->getFreeInvocableFunction(),
                        {
                            scope->find(parameter->getParameterType()->getName()).value()->getValue(),
                        }
                );
            } else if (parameter->needsToBeFreed()) {
                auto typeValue = irInjector->inject(childBlock, parameter->getParameterType()->getIRType(), irModule);
                auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(
                        parameter->getParameterType()->getIRType()->getValue()->getAllocatedType(), typeValue,
                        childBlock
                );
                DebugIRInjectorHelper::injectLog(irBlockNode, "[free-parameter] " + parameter->getParameterType()->getName() + " - " + irBlockNode->getBlock()->getParent()->getName().str(), irInjector, irModule);
                childBlock->getBuilder()->get()->CreateCall(
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