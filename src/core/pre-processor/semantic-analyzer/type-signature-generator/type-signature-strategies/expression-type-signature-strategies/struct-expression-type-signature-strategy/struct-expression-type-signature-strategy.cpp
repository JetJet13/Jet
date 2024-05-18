//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/struct-type-signature/struct-type-signature.h"

TypeSignature* StructExpressionTypeSignatureStrategy::create(ASTStructExpressionNode* structExpression, TypeSignatureLookupTable* scope, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = new StructTypeSignature();
    for (auto keyValuePair : structExpression->getKeyValuePairs()) {
        auto key = keyValuePair->getKey()->getIdentifierNode()->getValue(tokenTable);
        structTypeSignature->addKeyValuePair(
            key, strategyMap->getTypeSignatureForExpression(keyValuePair->getValue(), scope)
        );
    }

    return structTypeSignature;
}