//
// Created by Johny Georges on 2025-01-11.
//

#include "function-declaration-ir-injector-strategy.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"

void FunctionDeclarationIRInjectorStrategy::inject(IRFunctionDeclarationNode* irFunctionDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto variablesThatRequireFreeing = std::vector<IRVariableDeclarationNode*>();
    for (auto statement : *irFunctionDeclaration->getBlock()->getBody()) {
        irInjector->inject(irFunctionDeclaration->getBlock(), statement, irModule, irFunctionDeclaration->getScope());
        if (statement->is(IR_VARIABLE_DECLARATION_NODE)) {
            auto irVariableNode = (IRVariableDeclarationNode*)statement;
            if (irVariableNode->requiresFreeing()) {
                variablesThatRequireFreeing.push_back(irVariableNode);
            }
        }
    }
    for (auto variableToFree : variablesThatRequireFreeing) {
        auto typeValue = irInjector->inject(irFunctionDeclaration->getBlock(), variableToFree->getAllocatedIRType());
        auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(variableToFree->getAllocatedIRType()->getValue()->getAllocatedType(), typeValue);
        irFunctionDeclaration->getBlock()->getBuilder()->get()->CreateCall(
            irModule->getFreeValueFunction()->getFunctionType(),
            irModule->getFreeValueFunction(),
            {
                variableToFree->getValue(),
                loadedTypeValue
            }
        );
    }
}