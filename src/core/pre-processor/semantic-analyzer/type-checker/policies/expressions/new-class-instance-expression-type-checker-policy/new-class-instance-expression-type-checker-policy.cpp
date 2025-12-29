//
// Created by Johny Georges on 2024-05-29.
//

#include "new-class-instance-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace NewClassInstanceExpressionTypeCheckerPolicy {
    void apply(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(newClassInstanceExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(newClassInstanceExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(newClassInstanceExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            newClassInstanceExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        if (newClassInstanceExpression->getTypeSignature()->typeTargetIs(CLASS_TYPE_SOURCE)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNotClassType(newClassInstanceExpression)());
        }

        if (!newClassInstanceExpression->getTypeSignature()->hasConstructorInfo()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNoMatchingConstructor(newClassInstanceExpression)());
        }

        TypeChecker::applyPolicyTo(newClassInstanceExpression->getArguments(), typeCheckerResult);
    }
}