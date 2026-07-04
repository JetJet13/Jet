//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-property-type-signature-strategy.h"

void InterfacePropertyTypeSignatureStrategy::assign(std::shared_ptr<ASTInterfacePropertyNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), context, scope);
    node->setTypeSignature(new InterfacePropertyTypeSignature(node->getName()->getId(), node->getType()->getTypeSignature()));
}