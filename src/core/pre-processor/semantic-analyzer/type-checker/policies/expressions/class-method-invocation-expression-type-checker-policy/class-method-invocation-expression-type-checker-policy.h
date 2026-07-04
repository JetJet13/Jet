//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"

namespace ClassMethodInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassMethodInvocationExpressionNode> classMethodInvocationExpression, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_CHECKER_POLICY_H
