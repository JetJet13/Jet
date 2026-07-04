//
// Created by Johny Georges on 2026-06-24.
//

#include "class-circular-reference-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

void ClassCircularReferenceTypeCheckerRule::enforce(std::shared_ptr<ClassTypeSignature> classTypeSignature, std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    auto propertyTypeSignature = classPropertyTypeSignature->getType();
    if (propertyTypeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        propertyTypeSignature = (std::dynamic_pointer_cast<RefTypeSignature>(propertyTypeSignature)->getUnderlyingType());
    }

    if (propertyTypeSignature->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto otherClassInstanceTypeSignature = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(propertyTypeSignature);
        if (classTypeSignature->hasCircularReferenceWith(otherClassInstanceTypeSignature->getClass())) {
            typeCheckerResult->addError(message());
        }
    }
}

TypeCheckerRuleType ClassCircularReferenceTypeCheckerRule::getType() {
    return CLASS_CIRCULAR_REFERENCE_TCR;
}

std::string ClassCircularReferenceTypeCheckerRule::toString() {
    return "CLASS_CIRCULAR_REFERENCE";
}

bool ClassCircularReferenceTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void ClassCircularReferenceTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}