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

#include "unique-type-signature-keys-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void UniqueTypeSignatureKeysTypeCheckerRule::enforce(std::vector<std::string>* keys, ErrorMessageLambda& nonUniqueMessage, TypeCheckerResult* typeCheckerResult) {
    auto sameKeys = std::vector<std::string>();
    for (uint64_t i = 0; i < keys->size(); ++i) {
        for (uint64_t j = i + 1; j < keys->size(); ++j) {
            auto key = keys->at(i);
            auto otherKey = keys->at(j);
            if (key == otherKey) {
                sameKeys.push_back(key);
            }
        }
    }

    if (!sameKeys.empty()) {
        typeCheckerResult->addError(nonUniqueMessage());
    }

}

TypeCheckerRuleType UniqueTypeSignatureKeysTypeCheckerRule::getType() {
    return UNIQUE_TYPE_SIGNATURE_KEYS_TCR;
}

std::string UniqueTypeSignatureKeysTypeCheckerRule::toString() {
    return "UNIQUE_TYPE_SIGNATURE_KEYS";
}

bool UniqueTypeSignatureKeysTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueTypeSignatureKeysTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}