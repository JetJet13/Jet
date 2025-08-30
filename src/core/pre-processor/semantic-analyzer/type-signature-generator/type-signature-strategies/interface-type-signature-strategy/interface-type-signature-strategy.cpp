//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-signature-strategy.h"

void InterfaceTypeSignatureStrategy::assign(ASTInterfaceTypeDeclarationNode* interfaceTypeDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, scope);
        interfaceTypeDeclaration->getTypeSignature()->addProperty(
            property->getTypeSignature()->getName(),
            property->getTypeSignature()->getTypeSignature()->convertToVariableTypeSignature()
        );
    }

}