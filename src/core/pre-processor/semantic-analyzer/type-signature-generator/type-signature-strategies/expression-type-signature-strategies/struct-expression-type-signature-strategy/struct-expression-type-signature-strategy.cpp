//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/struct-type-signature/struct-type-signature.h"

void StructExpressionTypeSignatureStrategy::assign(ASTStructExpressionNode* structExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = new StructTypeSignature();
    for (auto keyValuePair : structExpression->getKeyValuePairs()) {
        strategyMap->assignTypeSignatureForExpression(keyValuePair->getValue(), scope);
        structTypeSignature->addKeyValuePair(
                keyValuePair->getKey()->getIdentifierNode()->getId(),
                keyValuePair->getValue()->getTypeSignature()
        );
    }

    structExpression->setTypeSignature(structTypeSignature);
}