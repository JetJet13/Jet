//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_FUNCTION_RETURN_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_RETURN_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-function-return-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class FunctionReturnIRInjectorStrategy {
public:
    void inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_FUNCTION_RETURN_IR_INJECTOR_STRATEGY_H
