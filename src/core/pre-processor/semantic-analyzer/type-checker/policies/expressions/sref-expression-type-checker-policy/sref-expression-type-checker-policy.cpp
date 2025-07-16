//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace SrefExpressionTypeCheckerPolicy {
    void apply(ASTSrefExpressionNode* srefExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(srefExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(srefExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(srefExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            srefExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto srefExpressionInvalidMessage = TypeCheckerErrorMessageTable::SrefExpressionTypeInvalid(srefExpression);
        TypeCheckerRuleProvider::getSrefTypeSignatureTypeCheckerRule()
        ->enforce(
            srefExpression->getExpressionNode()->getTypeSignature(),
            srefExpressionInvalidMessage,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(srefExpression->getExpressionNode(), typeCheckerResult);
    }
}