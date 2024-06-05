//
// Created by Johny Georges on 2024-05-29.
//

#include "tuple-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace TupleExpressionTypeCheckerPolicy {
    void apply(ASTTupleExpressionNode* tupleExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleExpression),
            typeCheckerResult
        );

        for (auto tupleItem : tupleExpression->getTupleList()->getItems()) {
            TypeChecker::applyPolicyTo(tupleItem->getItem(), typeCheckerResult);
        }
    }
}