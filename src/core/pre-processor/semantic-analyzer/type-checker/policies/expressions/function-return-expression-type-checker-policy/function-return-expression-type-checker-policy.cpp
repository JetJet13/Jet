//
// Created by Johny Georges on 2024-05-27.
//

#include "function-return-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace FunctionReturnExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionReturnExpressionNode> functionReturnExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto expression = functionReturnExpression->getExpression();
        if (expression) {
            TypeChecker::applyPolicyTo(expression.value(), typeCheckerResult, fileScope);
        }
    }
}