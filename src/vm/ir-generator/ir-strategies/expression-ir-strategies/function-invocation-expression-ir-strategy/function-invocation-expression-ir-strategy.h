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
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H
