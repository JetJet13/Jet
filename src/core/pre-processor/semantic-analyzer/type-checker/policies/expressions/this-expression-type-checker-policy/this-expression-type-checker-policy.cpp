//
// Created by Johny Georges on 2024-05-29.
//

#include "this-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ThisExpressionTypeCheckerPolicy {
    void apply(ASTThisExpressionNode* thisExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            thisExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(thisExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(thisExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(thisExpression),
            typeCheckerResult
        );

        if (thisExpression->getTypeSignature()->is(CLASS_TYPE_SOURCE)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNotClassType(thisExpression));
        }
    }
}