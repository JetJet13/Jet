//
// Created by Johny Georges on 2024-10-17.
//

#ifndef JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

class IRInjectorMap;

class FunctionParameterIRInjectorStrategy {
public:
    void inject(IRFunctionParameterDeclarationNode* irFunctionParameterDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule);
};

#endif //JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H
