//
// Created by Johny Georges on 2024-05-29.
//

#include "struct-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace StructExpressionTypeCheckerPolicy {
    void apply(ASTStructExpressionNode* structExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            structExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(structExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(structExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(structExpression),
            typeCheckerResult
        );

        for (auto keyValuePair : structExpression->getKeyValuePairs()) {
            TypeChecker::applyPolicyTo(keyValuePair->getValue(), typeCheckerResult);
        }

    }
}