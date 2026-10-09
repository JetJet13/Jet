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
// Created by Johny Georges on 2024-05-28.
//

#include "unique-type-signature-with-id-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void UniqueTypeSignatureWithIdTypeCheckerRule::enforce(std::vector<std::pair<std::string, std::shared_ptr<TypeSignature>>>* pairs, ErrorMessageLambda& nonUniqueMessage, TypeCheckerResult* typeCheckerResult) {
    auto samePairs = std::vector<std::pair<std::string, std::shared_ptr<TypeSignature>>>();
    for (uint64_t i = 0; i < pairs->size(); ++i) {
        for (uint64_t j = i + 1; j < pairs->size(); ++j) {
            auto pair = pairs->at(i);
            auto otherPair = pairs->at(j);
            if (pair.first == otherPair.first && pair.second->isEquivalentTo(otherPair.second)) {
                samePairs.push_back(pair);
            }
        }
    }

    if (!samePairs.empty()) {
        typeCheckerResult->addError(nonUniqueMessage());
    }

}

TypeCheckerRuleType UniqueTypeSignatureWithIdTypeCheckerRule::getType() {
    return UNIQUE_TYPE_SIGNATURE_WITH_ID_TCR;
}

std::string UniqueTypeSignatureWithIdTypeCheckerRule::toString() {
    return "UNIQUE_TYPE_SIGNATURE_WITH_ID";
}

bool UniqueTypeSignatureWithIdTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueTypeSignatureWithIdTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}