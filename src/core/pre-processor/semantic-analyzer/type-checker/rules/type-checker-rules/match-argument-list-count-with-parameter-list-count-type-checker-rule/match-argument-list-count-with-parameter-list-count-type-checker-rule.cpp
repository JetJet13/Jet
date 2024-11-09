//
// Created by Johny Georges on 2024-05-29.
//

#include "match-argument-list-count-with-parameter-list-count-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

bool MatchArgumentListCountWithParameterListCountTypeCheckerRule::enforce(unsigned long numParameters, unsigned long numArguments, std::string notEnoughArgumentsMessage, std::string tooManyArgumentsMessage, TypeCheckerResult* typeCheckerResult) {
    if (numArguments < numParameters) {
        typeCheckerResult->addError(notEnoughArgumentsMessage);
        return false;
    } else if (numArguments > numParameters) {
        typeCheckerResult->addError(tooManyArgumentsMessage);
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