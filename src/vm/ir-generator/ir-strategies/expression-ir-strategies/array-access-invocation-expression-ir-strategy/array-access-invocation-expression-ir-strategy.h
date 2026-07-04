//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"

class ArrayAccessInvocationExpressionIRStrategy {
public:
    IRExpressionNode* generate(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
