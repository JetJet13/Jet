//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

namespace ObjectAccessInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
