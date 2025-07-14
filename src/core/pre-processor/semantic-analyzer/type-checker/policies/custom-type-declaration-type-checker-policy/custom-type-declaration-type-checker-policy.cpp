//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace CustomTypeDeclarationTypeCheckerPolicy {
    void apply(ASTCustomTypeDeclarationNode* customTypeDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ParameterTypeUnknown(customTypeDeclarationNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::ParameterTypeInvalid(customTypeDeclarationNode);
        auto voidMessage = TypeCheckerErrorMessageTable::ParameterTypeVoid(customTypeDeclarationNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            customTypeDeclarationNode,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}