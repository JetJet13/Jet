//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"

namespace ArrayAccessInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> arrayAccessInvocationExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
