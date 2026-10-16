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
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"
#include "../../../../types/function-id-generator/function-id-generator.h"

void ParameterListItemTypeSignatureStrategy::assignAndAddToScope(std::shared_ptr<ASTFunctionParameterNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), context, scope);
    node->setTypeSignature(std::make_shared<ParameterListItemTypeSignature>(
        node->getIdentifier()->getIdentifierNode()->getId(),
        node->getType()->getTypeSignature()->convertToVariableTypeSignature()
    ));
}