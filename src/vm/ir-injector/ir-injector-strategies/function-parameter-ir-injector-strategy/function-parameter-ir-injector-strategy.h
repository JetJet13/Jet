//
// Created by Johny Georges on 2024-10-17.
//

#ifndef JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class FunctionParameterIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRFunctionParameterDeclarationNode> irFunctionParameterDeclaration, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
};

#endif //JETLANG_FUNCTION_PARAMETER_IR_INJECTOR_STRATEGY_H
