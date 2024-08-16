//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_FUNCTION_RETURN_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_RETURN_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-statement-nodes/ir-function-return-expression-node.h"

class FunctionReturnIRInjectorStrategy {
public:
    void inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_FUNCTION_RETURN_IR_INJECTOR_STRATEGY_H
