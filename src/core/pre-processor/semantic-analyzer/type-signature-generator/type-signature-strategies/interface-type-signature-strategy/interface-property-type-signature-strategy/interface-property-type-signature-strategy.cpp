//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-property-type-signature-strategy.h"

void InterfacePropertyTypeSignatureStrategy::assign(ASTInterfacePropertyNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), scope);
    node->setTypeSignature(new InterfacePropertyTypeSignature(node->getName()->getId(), node->getType()->getTypeSignature()));
}