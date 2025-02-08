//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace DrefExpressionTypeCheckerPolicy {
    void apply(ASTDrefExpressionNode* drefExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            drefExpression->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(drefExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(drefExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(drefExpression),
            typeCheckerResult
        );
        TypeCheckerRuleProvider::getDrefTypeSignatureTypeCheckerRule()
        ->enforce(
            drefExpression->getExpressionNode()->getTypeSignature(),
            TypeCheckerErrorMessageTable::DrefExpressionTypeInvalid(drefExpression),
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(drefExpression->getExpressionNode(), typeCheckerResult);
    }
}