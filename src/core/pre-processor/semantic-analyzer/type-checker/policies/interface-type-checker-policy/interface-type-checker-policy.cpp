//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace InterfaceTypeDeclarationTypeCheckerPolicy {
    void apply(ASTInterfaceTypeDeclarationNode* interfaceTypeDeclaration, TypeCheckerResult* typeCheckerResult) {
        auto propertyNames = std::vector<std::string>();
        for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
            propertyNames.push_back(property->getName()->getId());
            TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
            ->enforce(
                property->getTypeSignature()->getTypeSignature(),
                TypeCheckerErrorMessageTable::InterfacePropertyTypeUnknown(property),
                TypeCheckerErrorMessageTable::InterfacePropertyTypeInvalid(property),
                TypeCheckerErrorMessageTable::InterfacePropertyTypeVoid(property),
                typeCheckerResult
            );
        }

        TypeCheckerRuleProvider::getUniqueTypeSignatureKeysTypeCheckerRule()
        ->enforce(
                &propertyNames,
                TypeCheckerErrorMessageTable::InterfacePropertyNamesNotUnique(interfaceTypeDeclaration),
                typeCheckerResult
        );
    }
}