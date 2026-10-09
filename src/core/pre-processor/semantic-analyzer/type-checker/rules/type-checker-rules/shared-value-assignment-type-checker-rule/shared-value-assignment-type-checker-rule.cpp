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
// Created by Johny Georges on 2026-02-18.
//

#include "shared-value-assignment-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void SharedValueAssignmentTypeCheckerRule::enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage());
    }
}

void SharedValueAssignmentTypeCheckerRule::enforce(std::shared_ptr<SharedTypeSignature> sourceTypeSignature, std::shared_ptr<TypeSignature> valueTypeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!sourceTypeSignature->getUnderlyingType()->isEquivalentTo(valueTypeSignature)) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType SharedValueAssignmentTypeCheckerRule::getType() {
    return SHARED_VALUE_ASSIGNMENT_TCR;
}

std::string SharedValueAssignmentTypeCheckerRule::toString() {
    return "SHARED_VALUE_ASSIGNMENT";
}

bool SharedValueAssignmentTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void SharedValueAssignmentTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}