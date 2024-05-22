//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"

void ParameterListItemTypeSignatureStrategy::assign(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForType(node->getType(), scope);
    node->setTypeSignature(new ParameterListItemTypeSignature(
        node->getIdentifier()->getIdentifierNode()->getId(),
        node->getType()->getTypeSignature()
    ));
}