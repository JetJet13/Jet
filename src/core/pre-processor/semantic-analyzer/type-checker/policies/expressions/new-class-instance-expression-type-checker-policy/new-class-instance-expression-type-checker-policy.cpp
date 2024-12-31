//
// Created by Johny Georges on 2024-05-29.
//

#include "new-class-instance-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace NewClassInstanceExpressionTypeCheckerPolicy {
    void apply(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            newClassInstanceExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(newClassInstanceExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(newClassInstanceExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(newClassInstanceExpression),
            typeCheckerResult
        );

        if (newClassInstanceExpression->getTypeSignature()->typeTargetIs(CLASS_TYPE_SOURCE)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNotClassType(newClassInstanceExpression));
        }

        if (!newClassInstanceExpression->getTypeSignature()->hasConstructorInfo()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNoMatchingConstructor(newClassInstanceExpression));
        }
    }
}