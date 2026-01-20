//
// Created by Johny Georges on 2024-10-17.
//

#include "function-parameter-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void FunctionParameterIRInjectorStrategy::inject(IRFunctionParameterDeclarationNode* irFunctionParameterDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    InstructionIRInjectorHelper::inject(irFunctionParameterDeclaration->getAllocation(), irBlock);
    InstructionIRInjectorHelper::injectStore(irFunctionParameterDeclaration->getArgument(), irFunctionParameterDeclaration->getAllocation()->getValue(), irBlock, irFunctionParameterDeclaration->getAllocation()->getIRType());
    if (irFunctionParameterDeclaration->getArc()) {
        auto arcValue = InstructionIRInjectorHelper::inject(irFunctionParameterDeclaration->getArc().value(), irBlock, "arc");
    }
}