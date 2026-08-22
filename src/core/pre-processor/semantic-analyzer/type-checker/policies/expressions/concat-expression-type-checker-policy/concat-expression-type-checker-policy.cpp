//
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ConcatExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTConcatExpressionNode> concatExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(concatExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(concatExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(concatExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            concatExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}