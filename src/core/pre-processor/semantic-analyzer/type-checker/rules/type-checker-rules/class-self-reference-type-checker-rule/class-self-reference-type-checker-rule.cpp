//
// Created by Johny Georges on 2026-06-24.
//

#include "class-self-reference-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void ClassSelfReferenceTypeCheckerRule::enforce(std::shared_ptr<ClassTypeSignature> classTypeSignature, std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    auto propertyTypeSignature = classPropertyTypeSignature->getType();
    if (propertyTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        propertyTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(propertyTypeSignature)->getUnderlyingType());
    }

    if (propertyTypeSignature->isEquivalentTo(classTypeSignature)) {
        typeCheckerResult->addError(message());
    }
}

TypeCheckerRuleType ClassSelfReferenceTypeCheckerRule::getType() {
    return CLASS_SELF_REFERENCE_TCR;
}

std::string ClassSelfReferenceTypeCheckerRule::toString() {
    return "CLASS_SELF_REFERENCE";
}

bool ClassSelfReferenceTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void ClassSelfReferenceTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}