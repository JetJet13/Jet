//
// Created by Johny Georges on 2025-12-26.
//

#include "class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../unknown-type-signature/unknown-type-signature.h"

ClassInstanceTypeSignature::ClassInstanceTypeSignature() {
    _class = new ClassTypeSignature();
}

ClassInstanceTypeSignature::ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature) {
    _class = classTypeSignature;
}

bool ClassInstanceTypeSignature::isEmpty() {
    return _class->getInterface()->size() == 0;
}

TypeSignatureMap<ClassPropertyTypeSignature>* ClassInstanceTypeSignature::getProperties() {
    return _class->getProperties();
}

TypeSignatureMap<TypeSignature>* ClassInstanceTypeSignature::getKeyValuePairs() {
    return _class->getInterface();
}

TypeSignature* ClassInstanceTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _class->getInterface()->find(key);
    if (result) {
        return result.value();
    }
    return new UnknownTypeSignature();
}

TypeSignature* ClassInstanceTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= _class->getInterface()->size()) {
        return new UnknownTypeSignature();
    }

    return _class->getInterface()->find(_class->getInterface()->findKeyByIndex(index)).value();
}


std::string ClassInstanceTypeSignature::toDetailString() {
    return "jet.class.interface." + this->getId();
}

std::string ClassInstanceTypeSignature::toString() {
    return "CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource ClassInstanceTypeSignature::getTypeSource() {
    return CLASS_INSTANCE_TYPE_SOURCE;
}

bool ClassInstanceTypeSignature::isEqualTo(TypeSignature* otherType) {
    return  _class->isEqualTo(otherType);
}

bool ClassInstanceTypeSignature::isEquivalentTo(TypeSignature *otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    }
    return _class->isEquivalentTo(otherType);
}

void ClassInstanceTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _class->print();
    Logger::log("----------");
}