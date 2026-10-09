// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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