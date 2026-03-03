//
// Created by Johny Georges on 2025-06-28.
//

#include "struct-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void StructTypeTypeSignatureStrategy::assign(ASTStructTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = new StructTypeSignature();
    for (auto keyValuePair : node->getKeyValueTypes()) {
        strategyMap->assignTypeSignatureFor(keyValuePair->getType(), scope);
        if (keyValuePair->getType()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
            node->setTypeSignature(new InvalidTypeSignature());
            return;
        }
        auto valueTypeSignature = keyValuePair->getType()->getTypeSignature()->convertToVariableTypeSignature();
        valueTypeSignature->setKeyId(keyValuePair->getName()->getId());
        structTypeSignature->addKeyValuePair(
                keyValuePair->getName()->getId(),
                valueTypeSignature
        );
    }

    node->setTypeSignature(structTypeSignature);
}