//
// Created by Johny Georges on 2025-02-01.
//

#include "ref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace RefExpressionTypeCheckerPolicy {
    void apply(ASTRefExpressionNode* refExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        refExpression->getTypeSignature(),
                        TypeCheckerErrorMessageTable::ExpressionTypeUnknown(refExpression),
                        TypeCheckerErrorMessageTable::ExpressionTypeInvalid(refExpression),
                        TypeCheckerErrorMessageTable::ExpressionTypeVoid(refExpression),
                        typeCheckerResult
                );

        TypeChecker::applyPolicyTo(refExpression->getExpressionNode(), typeCheckerResult);
    }
}