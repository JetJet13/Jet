//
// Created by Johny Georges on 2026-02-18.
//

#include "ref-value-assignment-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void RefValueAssignmentTypeCheckerRule::enforce(TypeSignature* typeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage());
    }
}

void RefValueAssignmentTypeCheckerRule::enforce(RefTypeSignature* sourceTypeSignature, TypeSignature* valueTypeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!sourceTypeSignature->getUnderlyingType()->isEquivalentTo(valueTypeSignature)) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType RefValueAssignmentTypeCheckerRule::getType() {
    return REF_VALUE_ASSIGNMENT_TCR;
}

std::string RefValueAssignmentTypeCheckerRule::toString() {
    return "REF_VALUE_ASSIGNMENT";
}

bool RefValueAssignmentTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void RefValueAssignmentTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}