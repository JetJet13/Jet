//
// Created by Johny Georges on 2024-10-17.
//

#include "function-parameter-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void FunctionParameterIRInjectorStrategy::inject(IRFunctionParameterDeclarationNode* irFunctionParameterDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule) {
    InstructionIRInjectorHelper::inject(irFunctionParameterDeclaration->getAllocation(), irBlock);
    irBlock->getBuilder()->get()->CreateStore(irFunctionParameterDeclaration->getArgument(), irFunctionParameterDeclaration->getAllocation()->getValue());
}