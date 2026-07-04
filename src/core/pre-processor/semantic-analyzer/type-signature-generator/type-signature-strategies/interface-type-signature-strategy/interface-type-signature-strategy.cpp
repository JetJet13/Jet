//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-signature-strategy.h"

void InterfaceTypeSignatureStrategy::assign(std::shared_ptr<ASTInterfaceTypeDeclarationNode> interfaceTypeDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, context, scope);
        auto propertyTypeSignature = property->getPropertyTypeSignature()->getTypeSignature()->convertToVariableTypeSignature();
        auto name = property->getPropertyTypeSignature()->getName();
        interfaceTypeDeclaration->getInterfaceTypeSignature()->addProperty(
            name,
            propertyTypeSignature
        );
    }
}