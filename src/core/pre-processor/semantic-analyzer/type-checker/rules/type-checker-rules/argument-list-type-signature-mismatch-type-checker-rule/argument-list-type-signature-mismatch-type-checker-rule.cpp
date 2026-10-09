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
// Created by Johny Georges on 2024-05-29.
//

#include "argument-list-type-signature-mismatch-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ArgumentListTypeSignatureMismatchTypeCheckerRule::enforce(std::vector<std::shared_ptr<TypeSignature>>* parameterList, std::shared_ptr<ASTFunctionArgumentListNode> argumentList,  ErrorMessageLambda& mismatchMessage, TypeCheckerResult* typeCheckerResult) {
    for (uint64_t i = 0; i < parameterList->size(); i++) {
        if (!parameterList->at(i)->isEquivalentTo(
                argumentList->getArguments()->at(i)->getArgument()->getTypeSignature()->getTargetTypeSignature())) {
            typeCheckerResult->addError(mismatchMessage());
        }
    }
}

TypeCheckerRuleType ArgumentListTypeSignatureMismatchTypeCheckerRule::getType() {
    return ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH_TCR;
}

std::string ArgumentListTypeSignatureMismatchTypeCheckerRule::toString() {
    return "ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH";
}

bool ArgumentListTypeSignatureMismatchTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void ArgumentListTypeSignatureMismatchTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}