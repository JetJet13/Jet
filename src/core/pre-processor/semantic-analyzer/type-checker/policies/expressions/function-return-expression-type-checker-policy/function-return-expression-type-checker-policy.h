//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"
#include "../../../types/type-checker-result/type-checker-result.h"

namespace FunctionReturnExpressionTypeCheckerPolicy {
    void apply(ASTFunctionReturnExpressionNode* functionReturnExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_CHECKER_POLICY_H
