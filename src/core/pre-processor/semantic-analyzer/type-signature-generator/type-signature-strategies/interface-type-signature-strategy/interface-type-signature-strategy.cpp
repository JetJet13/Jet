//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-signature-strategy.h"

void InterfaceTypeSignatureStrategy::assign(ASTInterfaceTypeDeclarationNode* interfaceTypeDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto interfaceTypeSignature = (InterfaceTypeSignature*)scope->findGlobal(interfaceTypeDeclaration->getId());
    if (interfaceTypeDeclaration->getProperties()->getProperties().empty()) {
        interfaceTypeDeclaration->setTypeSignature(interfaceTypeSignature);
        return;
    }

    for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, scope);
        interfaceTypeSignature->addProperty(
            property->getTypeSignature()->getName(),
            property->getTypeSignature()->getTypeSignature()->convertToVariableTypeSignature()
        );
    }

    interfaceTypeDeclaration->setTypeSignature(interfaceTypeSignature);
}