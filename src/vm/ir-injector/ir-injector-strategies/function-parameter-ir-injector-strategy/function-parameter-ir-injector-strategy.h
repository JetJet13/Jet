//
// Created by Johny Georges on 2024-10-17.
//

#ifndef JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class FunctionParameterIRInjectorStrategy {
public:
    void inject(IRFunctionParameterDeclarationNode* irFunctionParameterDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule);
};

#endif //JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H
