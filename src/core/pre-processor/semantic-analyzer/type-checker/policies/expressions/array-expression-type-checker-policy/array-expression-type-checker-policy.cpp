//
// Created by Johny Georges on 2024-05-28.
//

#include "array-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../../shared/utils/logger/logger.h"

namespace ArrayExpressionTypeCheckerPolicy {
    void apply(ASTArrayExpressionNode* arrayExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayExpression->getTypeSignature()->getElementType(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayExpression),
            typeCheckerResult
        );

        for (auto element : *arrayExpression->getElements()) {
            Logger::log("!!--!!");
            arrayExpression->getTypeSignature()->getElementType()->print();
            Logger::log("!!!!!!");
            element->getTypeSignature()->print();
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                arrayExpression->getTypeSignature()->getElementType(),
                element->getTypeSignature(),
                TypeCheckerErrorMessageTable::ArrayElementTypeMismatch(element),
                typeCheckerResult
            );
        }
    }
}