//
// Created by Johny Georges on 2025-06-28.
//

#include "struct-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void StructTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTStructTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = std::make_shared<StructTypeSignature>();
    for (auto keyValuePair : node->getKeyValueTypes()) {
        strategyMap->assignTypeSignatureFor(keyValuePair->getType(), context, scope);
        if (keyValuePair->getType()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
            node->setTypeSignature(std::make_shared<InvalidTypeSignature>());
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