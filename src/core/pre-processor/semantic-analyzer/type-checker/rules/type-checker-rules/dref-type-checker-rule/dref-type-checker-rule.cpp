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
// Created by Johny Georges on 2025-02-08.
//

#include "dref-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void DrefTypeSignatureTypeCheckerRule::enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType DrefTypeSignatureTypeCheckerRule::getType() {
    return DREF_TYPE_SIGNATURE_TCR;
}

std::string DrefTypeSignatureTypeCheckerRule::toString() {
    return "DREF_TYPE_SIGNATURE";
}

bool DrefTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void DrefTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}