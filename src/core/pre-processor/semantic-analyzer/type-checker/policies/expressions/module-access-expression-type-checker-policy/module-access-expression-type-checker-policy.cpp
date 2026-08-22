//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ModuleAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(moduleAccessExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(moduleAccessExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(moduleAccessExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        moduleAccessExpression,
                        unknownMessage,
                        invalidMessage,
                        voidMessage,
                        typeCheckerResult
                );
    }
}