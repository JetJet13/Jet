//
// Created by Johny Georges on 2024-05-29.
//

#include "struct-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace StructExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTStructExpressionNode> structExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(structExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(structExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(structExpression);

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            structExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        for (auto keyValuePair : structExpression->getKeyValuePairs()) {
            TypeChecker::applyPolicyTo(keyValuePair->getValue(), typeCheckerResult);
        }

    }
}