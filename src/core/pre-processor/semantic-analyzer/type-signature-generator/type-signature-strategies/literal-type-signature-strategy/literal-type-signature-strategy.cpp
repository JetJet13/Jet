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
// Created by Johny Georges on 2024-05-13.
//

#include "literal-type-signature-strategy.h"


void LiteralTypeSignatureStrategy::assign(std::shared_ptr<ASTLiteralNode> literalNode, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable) {
    auto literalSymbol = literalNode->getLiteral()->getToken()->getSymbol();
    if (literalSymbol->isInt()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getIntLiteralTypeSignature());
    } else if (literalSymbol->isFloat()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getFloatLiteralTypeSignature());
    } else if (literalSymbol->isChar()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getCharLiteralTypeSignature());
    } else if (literalSymbol->isString()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getStringLiteralTypeSignature());
    } else if (literalSymbol->isBoolean()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getBoolLiteralTypeSignature());
    } else {
        throw std::invalid_argument("unknown literal node");
    }
}