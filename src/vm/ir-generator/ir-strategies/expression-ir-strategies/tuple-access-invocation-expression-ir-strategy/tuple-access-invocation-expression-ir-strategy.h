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
    IRExpressionNode* generate(ASTTupleAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};

#endif //JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
