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