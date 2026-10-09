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

#include "match-argument-list-count-with-parameter-list-count-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

bool MatchArgumentListCountWithParameterListCountTypeCheckerRule::enforce(uint64_t numParameters, uint64_t numArguments, bool isVariableLength, ErrorMessageLambda& notEnoughArgumentsMessage, ErrorMessageLambda& tooManyArgumentsMessage, TypeCheckerResult* typeCheckerResult) {
    if (numArguments < numParameters) {
        typeCheckerResult->addError(notEnoughArgumentsMessage());
        return false;
    } else if (!isVariableLength && numArguments > numParameters) {
        typeCheckerResult->addError(tooManyArgumentsMessage());
        return false;
    }
    return true;
}

TypeCheckerRuleType MatchArgumentListCountWithParameterListCountTypeCheckerRule::getType() {
    return MATCH_ARGUMENT_LIST_COUNT_WITH_PARAMETER_LIST_COUNT_TCR;
}

std::string MatchArgumentListCountWithParameterListCountTypeCheckerRule::toString() {
    return "MATCH_ARGUMENT_LIST_COUNT_WITH_PARAMETER_LIST_COUNT";
}

bool MatchArgumentListCountWithParameterListCountTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void MatchArgumentListCountWithParameterListCountTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}