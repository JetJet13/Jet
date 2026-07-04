//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void StructExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTStructExpressionNode> structExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = new StructTypeSignature();
    for (auto keyValuePair : structExpression->getKeyValuePairs()) {
        strategyMap->assignTypeSignatureFor(keyValuePair->getValue(), context, scope);
        auto valueTypeSignature = keyValuePair->getValue()->getTypeSignature()->convertToVariableTypeSignature();
        valueTypeSignature->setKeyId(keyValuePair->getKey()->getIdentifierNode()->getId());
        structTypeSignature->addKeyValuePair(
                keyValuePair->getKey()->getIdentifierNode()->getId(),
                valueTypeSignature
        );
    }

    structExpression->setTypeSignature(structTypeSignature);
}