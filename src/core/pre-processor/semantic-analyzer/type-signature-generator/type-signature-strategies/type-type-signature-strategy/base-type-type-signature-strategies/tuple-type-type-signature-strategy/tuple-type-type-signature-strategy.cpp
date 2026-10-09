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
// Created by Johny Georges on 2024-05-09.
//

#include "tuple-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

void TupleTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = std::vector<std::shared_ptr<TypeSignature>>();
    for (auto type : node->getValueTypes()) {
        strategyMap->assignTypeSignatureFor(type, context, scope);
        typeSignatures.push_back(type->getTypeSignature());
    }
    node->setTypeSignature(std::make_shared<TupleTypeSignature>(typeSignatures));
}