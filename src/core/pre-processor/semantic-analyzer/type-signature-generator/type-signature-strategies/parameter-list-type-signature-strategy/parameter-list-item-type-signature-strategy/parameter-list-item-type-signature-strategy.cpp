//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ParameterListItemTypeSignatureStrategy::assignAndAddToScope(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), scope);
    node->setTypeSignature(new ParameterListItemTypeSignature(
        node->getIdentifier()->getIdentifierNode()->getId(),
        node->getType()->getTypeSignature()
    ));
    scope->insert(node->getIdentifier()->getIdentifierNode()->getId(), node->getType()->getTypeSignature());
}