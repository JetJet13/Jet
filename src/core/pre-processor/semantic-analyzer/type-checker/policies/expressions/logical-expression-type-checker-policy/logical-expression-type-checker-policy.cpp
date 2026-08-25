//
// Created by Johny Georges on 2024-05-29.
//

#include "logical-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace LogicalExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTLogicalExpressionNode> logicalExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(logicalExpression->getLeftNode(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(logicalExpression->getRightNode(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(logicalExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(logicalExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(logicalExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            logicalExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}