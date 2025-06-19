//
// Created by Johny Georges on 2025-06-18.
//

#ifndef JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"

namespace TupleAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTTupleAccessInvocationExpressionNode* tupleAccessInvocationExpression, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
