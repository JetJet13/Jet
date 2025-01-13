//
// Created by Johny Georges on 2024-10-17.
//

#include "function-parameter-ir-injector-strategy.h"

void FunctionParameterIRInjectorStrategy::inject(IRFunctionParameterDeclarationNode* irFunctionParameterDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule) {
    irBlock->getBuilder()->get()->Insert(irFunctionParameterDeclaration->getAllocation()->getValue());
    irBlock->getBuilder()->get()->CreateStore(irFunctionParameterDeclaration->getArgument(), irFunctionParameterDeclaration->getAllocation()->getValue());
}