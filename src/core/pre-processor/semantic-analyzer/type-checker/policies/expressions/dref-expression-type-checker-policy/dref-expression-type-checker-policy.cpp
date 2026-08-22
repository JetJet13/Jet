//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace DrefExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTDrefExpressionNode> drefExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(drefExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(drefExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(drefExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            drefExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
        auto drefInvalidMessage = TypeCheckerErrorMessageTable::DrefExpressionTypeInvalid(drefExpression);
        TypeCheckerRuleProvider::getDrefTypeSignatureTypeCheckerRule()
        ->enforce(
            drefExpression->getExpressionNode()->getTypeSignature(),
            drefInvalidMessage,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(drefExpression->getExpressionNode(), typeCheckerResult, fileScope);
    }
}