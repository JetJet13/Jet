// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void StructExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTStructExpressionNode> structExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto structTypeSignature = std::make_shared<StructTypeSignature>();
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