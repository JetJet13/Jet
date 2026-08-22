//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace InterfaceTypeDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTInterfaceTypeDeclarationNode> interfaceTypeDeclaration, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto propertyNames = std::vector<std::string>();
        for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
            propertyNames.push_back(property->getName()->getId());
            auto unknownMessage = TypeCheckerErrorMessageTable::InterfacePropertyTypeUnknown(property);
            auto invalidMessage = TypeCheckerErrorMessageTable::InterfacePropertyTypeInvalid(property);
            auto voidMessage = TypeCheckerErrorMessageTable::InterfacePropertyTypeVoid(property);
            TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
            ->enforce(
                property->getPropertyTypeSignature()->getTypeSignature(),
                unknownMessage,
                invalidMessage,
                voidMessage,
                typeCheckerResult
            );
        }
        auto propertyNamesNotUniqueMessage = TypeCheckerErrorMessageTable::InterfacePropertyNamesNotUnique(interfaceTypeDeclaration);
        TypeCheckerRuleProvider::getUniqueTypeSignatureKeysTypeCheckerRule()
        ->enforce(
            &propertyNames,
            propertyNamesNotUniqueMessage,
            typeCheckerResult
        );
    }
}