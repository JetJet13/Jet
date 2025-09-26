//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

class ObjectAccessInvocationExpressionIRStrategy {
public:
    IRExpressionNode* generate(ASTObjectAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_IR_STRATEGY_H
