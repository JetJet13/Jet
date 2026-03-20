//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-signature-strategy.h"

void InterfaceTypeSignatureStrategy::assign(ASTInterfaceTypeDeclarationNode* interfaceTypeDeclaration, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, context, scope);
        auto propertyTypeSignature = property->getTypeSignature()->getTypeSignature()->convertToVariableTypeSignature();
        auto name = property->getTypeSignature()->getName();
        interfaceTypeDeclaration->getTypeSignature()->addProperty(
            name,
            propertyTypeSignature
        );
    }

}