//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"

ParameterListItemTypeSignature* ParameterListItemTypeSignatureStrategy::create(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    return new ParameterListItemTypeSignature(
        node->getIdentifier()->getIdentifierNode()->getId(),
        strategyMap->getTypeSignatureForType(node->getType(), scope)
    );
}