//
// Created by Johny Georges on 2024-05-29.
//

#include "this-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ThisExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTThisExpressionNode> thisExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(thisExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(thisExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(thisExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            thisExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        if (thisExpression->getTypeSignature()->typeTargetIs(CLASS_TYPE_SOURCE)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNotClassType(thisExpression)());
        }
    }
}