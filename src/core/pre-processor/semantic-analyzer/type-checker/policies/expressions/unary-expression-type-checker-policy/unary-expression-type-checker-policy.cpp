//
// Created by Johny Georges on 2024-05-29.
//

#include "unary-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace UnaryExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTUnaryExpressionNode> unaryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(unaryExpression->getExpressionNode(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(unaryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(unaryExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(unaryExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            unaryExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

    }
}