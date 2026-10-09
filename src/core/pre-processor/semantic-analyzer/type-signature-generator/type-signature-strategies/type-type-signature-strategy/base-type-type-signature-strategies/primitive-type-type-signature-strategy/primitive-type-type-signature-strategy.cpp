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

#include "primitive-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void PrimitiveTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTPrimitiveTypeNode> node, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable) {
    auto symbol = node->getLexeme()->getToken()->getSymbol();
    if (symbol->isIntType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getIntLiteralTypeSignature());
    } else if (symbol->isFloatType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getFloatLiteralTypeSignature());
    } else if (symbol->isCharType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getCharLiteralTypeSignature());
    } else if (symbol->isStringType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getStringLiteralTypeSignature());
    } else if (symbol->isBooleanType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getBoolLiteralTypeSignature());
    } else {
        node->setTypeSignature(std::make_shared<InvalidTypeSignature>());
    }
}