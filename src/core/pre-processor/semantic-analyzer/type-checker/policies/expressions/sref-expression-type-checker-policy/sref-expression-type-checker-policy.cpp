//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace SrefExpressionTypeCheckerPolicy {
    void apply(ASTSrefExpressionNode* srefExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        srefExpression->getTypeSignature(),
                        TypeCheckerErrorMessageTable::ExpressionTypeUnknown(srefExpression),
                        TypeCheckerErrorMessageTable::ExpressionTypeInvalid(srefExpression),
                        TypeCheckerErrorMessageTable::ExpressionTypeVoid(srefExpression),
                        typeCheckerResult
                );
        TypeCheckerRuleProvider::getSrefTypeSignatureTypeCheckerRule()
                ->enforce(
                        srefExpression->getExpressionNode()->getTypeSignature(),
                        TypeCheckerErrorMessageTable::SrefExpressionTypeInvalid(srefExpression),
                        typeCheckerResult
                );
        TypeChecker::applyPolicyTo(srefExpression->getExpressionNode(), typeCheckerResult);
    }
}