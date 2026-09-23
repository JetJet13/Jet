//
// Created by Johny Georges on 2024-05-29.
//

#include "tuple-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace TupleExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTupleExpressionNode> tupleExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        for (uint64_t i = 0; i < tupleExpression->numItems(); ++i) {
            auto tupleItem = tupleExpression->getItems()->at(i);
            TypeChecker::applyPolicyTo(tupleItem->getItem(), typeCheckerResult, fileScope);
        }
    }
}