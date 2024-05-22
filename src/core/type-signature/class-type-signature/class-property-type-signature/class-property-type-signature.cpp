//
// Created by Johny Georges on 2024-05-03.
//

#include "class-property-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../unknown-type-signature/unknown-type-signature.h"

ClassPropertyTypeSignature::ClassPropertyTypeSignature() {
    _accessModifier = new AccessModifierTypeSignature();
    _isStatic = false;
    _isConst = false;
    _type = new UnknownTypeSignature();
}

ClassPropertyTypeSignature::ClassPropertyTypeSignature(AccessModifierTypeSignature* accessModifier, TypeSignature* type, bool isStatic, bool isConst) {
    _accessModifier = accessModifier;
    _isStatic = isStatic;
    _isConst = isConst;
    _type = type;
}

bool ClassPropertyTypeSignature::isStatic() {
    return _isStatic;
}

bool ClassPropertyTypeSignature::isConst() {
    return _isConst;
}

AccessModifierTypeSignature* ClassPropertyTypeSignature::getAccessModifier() {
    return _accessModifier;
}


TypeSignature* ClassPropertyTypeSignature::getType() {
    return _type;
}

void ClassPropertyTypeSignature::setType(TypeSignature* typeSignature) {
    _type = typeSignature;
}

std::string ClassPropertyTypeSignature::toString() {
    return "CLASS_PROPERTY_TYPE_SIGNATURE";
}

TypeSource ClassPropertyTypeSignature::getTypeSource() {
    return CLASS_PROPERTY_TYPE_SOURCE;
}

bool ClassPropertyTypeSignature::isEqualTo(TypeSignature *otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ClassPropertyTypeSignature*)otherType;
    return this->getAccessModifier()->isEqualTo(other->getAccessModifier()) &&
           this->getType()->isEqualTo(other->getType()) &&
           this->isStatic() == other->isStatic() &&
           this->isConst() == other->isConst();

}

void ClassPropertyTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("IS_STATIC - ", _isStatic);
    Logger::log("IS_CONST - ", _isConst);
    _accessModifier->print();
    _type->print();
    Logger::log("----------");
}