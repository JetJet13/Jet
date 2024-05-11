//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/struct-type-signature/struct-type-signature.h"

TypeSignature* StructExpressionTypeSignatureStrategy::create(ASTStructExpressionNode* structExpression, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = new StructTypeSignature();
    for (auto keyValuePair : structExpression->getKeyValuePairs()) {
        auto key = tokenTable->getIdentifier(keyValuePair->getKey()->getIdentifierNode()->getIdentifier()->getToken()->getValueId().value());
        if (!key) {
            throw std::invalid_argument("struct key not found in token table" + keyValuePair->getKey()->toString());
        }

        structTypeSignature->addKeyValuePair(
                new StructKeyValueTypeSignature(key.value(), strategyMap->getTypeSignatureFor(keyValuePair->getValue()))
        );
    }

    return structTypeSignature;
}