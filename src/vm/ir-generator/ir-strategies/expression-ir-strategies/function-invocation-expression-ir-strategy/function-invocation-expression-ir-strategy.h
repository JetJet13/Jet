//
// Created by Johny Georges on 2024-11-08.
//

#ifndef JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"

class FunctionInvocationExpressionIRStrategy {
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H
