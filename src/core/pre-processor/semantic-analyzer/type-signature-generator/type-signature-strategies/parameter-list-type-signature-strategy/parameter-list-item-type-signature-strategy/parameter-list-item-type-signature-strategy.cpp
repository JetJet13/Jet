//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"
#include "../../../../../../type-signature/parameter-list-type-signature/parameter-list-item-type-signature/parameter-list-item-type-signature.h"
#include "../../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"

TypeSignature* ParameterListItemTypeSignatureStrategy::create(ASTFunctionParameterNode* node, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    return new ParameterListItemTypeSignature(
        tokenTable->getIdentifier(node->getIdentifier()->getIdentifierNode()->getIdentifier()->getToken()->getValueId().value()).value(),
        strategyMap->getTypeSignatureFor(node->getType())
    );
}