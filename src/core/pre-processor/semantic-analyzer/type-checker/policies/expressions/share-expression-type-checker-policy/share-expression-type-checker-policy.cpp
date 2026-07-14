//
// Created by Johny Georges on 2026-07-11.
//

#include "share-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace ShareExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTShareExpressionNode> shareExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(shareExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(shareExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(shareExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        shareExpression->getTypeSignature(),
                        unknownMessage,
                        invalidMessage,
                        voidMessage,
                        typeCheckerResult
                );
        auto shareExpressionInvalidMessage = TypeCheckerErrorMessageTable::ShareExpressionTypeInvalid(shareExpression);
        TypeCheckerRuleProvider::getSharedTypeSignatureTypeCheckerRule()
                ->enforce(
                        shareExpression->getSharedTypeSignature(),
                        shareExpressionInvalidMessage,
                        typeCheckerResult
                );
        TypeChecker::applyPolicyTo(shareExpression->getExpressionNode(), typeCheckerResult);
    }
}