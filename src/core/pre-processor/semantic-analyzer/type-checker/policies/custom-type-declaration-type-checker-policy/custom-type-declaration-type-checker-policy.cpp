//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace CustomTypeDeclarationTypeCheckerPolicy {
    void apply(ASTCustomTypeDeclarationNode* customTypeDeclarationNode, TypeCheckerResult* typeCheckerResult) {

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        customTypeDeclarationNode,
                        TypeCheckerErrorMessageTable::ParameterTypeUnknown(
                                customTypeDeclarationNode
                        ),
                        TypeCheckerErrorMessageTable::ParameterTypeInvalid(
                                customTypeDeclarationNode
                        ),
                        TypeCheckerErrorMessageTable::ParameterTypeVoid(
                                customTypeDeclarationNode
                        ),
                        typeCheckerResult
                );
    }
}