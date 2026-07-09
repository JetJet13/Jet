//
// Created by Johny Georges on 2025-06-18.
//

#ifndef JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"

class TupleAccessInvocationExpressionIRStrategy {
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
