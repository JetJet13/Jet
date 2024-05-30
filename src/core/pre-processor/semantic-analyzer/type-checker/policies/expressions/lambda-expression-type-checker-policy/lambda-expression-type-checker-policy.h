//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_LAMBDA_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"

namespace LambdaExpressionTypeCheckerPolicy {
    void apply(ASTLambdaExpressionNode* lambdaExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_CHECKER_POLICY_H
