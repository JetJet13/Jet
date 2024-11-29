//
// Created by Johny Georges on 2024-10-17.
//

#include "function-parameter-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../ir-type/ir-function-parameter-type.h"

void FunctionParameterIRInjectorStrategy::inject(IRFunctionParameterDeclarationNode* irFunctionParameterDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule) {
    builder->get()->Insert(irFunctionParameterDeclaration->getAllocation()->getValue());
    builder->get()->CreateStore(irFunctionParameterDeclaration->getArgument(), irFunctionParameterDeclaration->getAllocation()->getValue());
}