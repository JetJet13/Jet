//
// Created by Johny Georges on 2024-05-29.
//

#include "logical-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace LogicalExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTLogicalExpressionNode> logicalExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(logicalExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(logicalExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(logicalExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            logicalExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}