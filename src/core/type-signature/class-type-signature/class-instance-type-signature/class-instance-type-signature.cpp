//
// Created by Johny Georges on 2024-05-15.
//

#include "class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ClassInstanceTypeSignature::ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature) {
    _classTypeSignature = classTypeSignature;
}

std::string ClassInstanceTypeSignature::toString() {
    return "CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource ClassInstanceTypeSignature::getTypeSource() {
    return CLASS_INSTANCE_TYPE_SOURCE;
}

bool ClassInstanceTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void ClassInstanceTypeSignature::print() {
    Logger::log(this->toString());
}