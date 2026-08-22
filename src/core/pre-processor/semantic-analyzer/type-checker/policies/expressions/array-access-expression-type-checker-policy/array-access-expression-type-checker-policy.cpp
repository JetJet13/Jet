//
// Created by Johny Georges on 2024-05-28.
//

#include "array-access-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ArrayAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayAccessExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayAccessExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}