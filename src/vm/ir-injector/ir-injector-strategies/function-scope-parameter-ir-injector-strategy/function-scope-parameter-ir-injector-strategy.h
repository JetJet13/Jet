//
// Created by Johny Georges on 2024-11-16.
//

#ifndef JETLANG_FUNCTION_SCOPE_PARAMETER_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_SCOPE_PARAMETER_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-statement-nodes/ir-function-return-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-type/ir-parameter-type.h"

class IRInjectorMap;

class FunctionScopeParameterIRInjectorStrategy {
public:
    void inject(IRParameterType* scopeParameter, IRModuleNode* irModule);
};

#endif //JETLANG_FUNCTION_SCOPE_PARAMETER_IR_INJECTOR_STRATEGY_H
