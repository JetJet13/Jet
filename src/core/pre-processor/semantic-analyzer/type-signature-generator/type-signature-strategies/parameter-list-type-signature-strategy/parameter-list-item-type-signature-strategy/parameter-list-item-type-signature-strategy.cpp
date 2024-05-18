//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"
#include "../../../../../../type-signature/parameter-list-type-signature/parameter-list-item-type-signature/parameter-list-item-type-signature.h"

ParameterListItemTypeSignature* ParameterListItemTypeSignatureStrategy::create(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    return new ParameterListItemTypeSignature(
        tokenTable->getIdentifier(node->getIdentifier()->getIdentifierNode()->getIdentifier()->getToken()->getValueId().value()).value(),
        strategyMap->getTypeSignatureForType(node->getType(), scope)
    );
}