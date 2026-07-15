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