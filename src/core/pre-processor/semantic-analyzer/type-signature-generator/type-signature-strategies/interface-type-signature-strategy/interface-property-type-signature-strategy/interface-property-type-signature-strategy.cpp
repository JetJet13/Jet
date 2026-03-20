//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-property-type-signature-strategy.h"

void InterfacePropertyTypeSignatureStrategy::assign(ASTInterfacePropertyNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), context, scope);
    node->setTypeSignature(new InterfacePropertyTypeSignature(node->getName()->getId(), node->getType()->getTypeSignature()));
}