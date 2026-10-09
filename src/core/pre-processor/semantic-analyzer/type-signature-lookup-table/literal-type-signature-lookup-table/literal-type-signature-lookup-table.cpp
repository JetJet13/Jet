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
// Created by Johny Georges on 2024-05-18.
//

#include "literal-type-signature-lookup-table.h"

std::shared_ptr<IntLiteralTypeSignature> LiteralTypeSignatureLookupTable::getIntLiteralTypeSignature() {
    return std::make_shared<IntLiteralTypeSignature>();
}

std::shared_ptr<FloatLiteralTypeSignature> LiteralTypeSignatureLookupTable::getFloatLiteralTypeSignature() {
    return std::make_shared<FloatLiteralTypeSignature>();
}

std::shared_ptr<CharLiteralTypeSignature> LiteralTypeSignatureLookupTable::getCharLiteralTypeSignature() {
    return std::make_shared<CharLiteralTypeSignature>();
}

std::shared_ptr<StringLiteralTypeSignature> LiteralTypeSignatureLookupTable::getStringLiteralTypeSignature() {
    return std::make_shared<StringLiteralTypeSignature>();
}

std::shared_ptr<BoolLiteralTypeSignature> LiteralTypeSignatureLookupTable::getBoolLiteralTypeSignature() {
    return std::make_shared<BoolLiteralTypeSignature>();
}