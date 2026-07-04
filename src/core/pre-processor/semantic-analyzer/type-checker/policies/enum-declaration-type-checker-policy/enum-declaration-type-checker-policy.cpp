//
// Created by Johny Georges on 2024-05-27.
//

#include "enum-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace EnumDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTEnumDeclarationNode> enumDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        for (auto enumKeyValue : enumDeclarationNode->getValues()->getParameters()) {
            auto mismatchMessage = TypeCheckerErrorMessageTable::EnumKeyValueTypeMismatch(enumDeclarationNode);
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                enumDeclarationNode->getTypeSignature()->getType(),
                enumKeyValue->getTypeSignature(),
                mismatchMessage,
                typeCheckerResult
            );
        }
    }
}