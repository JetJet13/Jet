//
// Created by Johny Georges on 2024-05-27.
//

#include "function-return-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace FunctionReturnExpressionTypeCheckerPolicy {
    void apply(ASTFunctionReturnExpressionNode* functionReturnExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(functionReturnExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(functionReturnExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            functionReturnExpression,
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );
    }
}