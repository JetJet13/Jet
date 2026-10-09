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
// Created by Johny Georges on 2024-05-27.
//

#include "iterable-type-signature-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void IterableTypeSignatureTypeCheckerRule::enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        typeCheckerResult->addError(message());
    }
}

TypeCheckerRuleType IterableTypeSignatureTypeCheckerRule::getType() {
    return ITERABLE_TYPE_SIGNATURE_TCR;
}

std::string IterableTypeSignatureTypeCheckerRule::toString() {
    return "ITERABLE_TYPE_SIGNATURE";
}

bool IterableTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void IterableTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}
