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
// Created by Johny Georges on 2024-12-31.
//

#include "argument-list-type-signature-strategy.h"

void ArgumentListTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionArgumentListNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto argumentTypes = std::vector<std::shared_ptr<TypeSignature>>();
    if (context->getTypeSignatures() && context->getTypeSignatures().value()->size() != node->numArguments()) {
        argumentTypes.push_back(std::make_shared<UnknownTypeSignature>());
        node->setTypeSignature(std::make_shared<ArgumentListTypeSignature>(argumentTypes));
        return;
    }
    for (int i = 0; i < node->numArguments(); ++i) {
        auto argument = node->getArguments()->at(i);
        auto argumentContext = context;
        if (context->getTypeSignatures()) {
            argumentContext = std::make_shared<TypeSignatureContext>(context->getTypeSignatures().value()->at(i));
        }
        strategyMap->assignTypeSignatureFor(argument->getArgument(), argumentContext, scope);
        argumentTypes.push_back(argument->getArgument()->getTypeSignature()->convertToVariableTypeSignature());
    }

    node->setTypeSignature(std::make_shared<ArgumentListTypeSignature>(argumentTypes));
}