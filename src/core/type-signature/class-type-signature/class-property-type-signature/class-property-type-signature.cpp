//
// Created by Johny Georges on 2024-05-03.
//

#include "class-property-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../unknown-type-signature/unknown-type-signature.h"

ClassPropertyTypeSignature::ClassPropertyTypeSignature() {
    _accessModifier = std::make_shared<AccessModifierTypeSignature>();
    _isStatic = false;
    _isConst = false;
    _type = std::make_shared<UnknownTypeSignature>();
}

ClassPropertyTypeSignature::ClassPropertyTypeSignature(std::shared_ptr<AccessModifierTypeSignature> accessModifier, std::shared_ptr<TypeSignature> type, bool isStatic, bool isConst) {
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

std::shared_ptr<AccessModifierTypeSignature> ClassPropertyTypeSignature::getAccessModifier() {
    return _accessModifier;
}


std::shared_ptr<TypeSignature> ClassPropertyTypeSignature::getType() {
    return _type;
}

void ClassPropertyTypeSignature::setType(std::shared_ptr<TypeSignature> typeSignature) {
    _type = typeSignature;
}

std::string ClassPropertyTypeSignature::toDetailString() {
    return "jet.class_property." + _type->toDetailString();
}

std::string ClassPropertyTypeSignature::toString() {
    return "CLASS_PROPERTY_TYPE_SIGNATURE";
}

TypeSource ClassPropertyTypeSignature::getTypeSource() {
    return CLASS_PROPERTY_TYPE_SOURCE;
}

TypeSource ClassPropertyTypeSignature::getTypeTarget() {
    return _type->getTypeSource();
}

bool ClassPropertyTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ClassPropertyTypeSignature>(otherType);
    return this->getAccessModifier()->isEqualTo(other->getAccessModifier()) &&
           this->getType()->isEqualTo(other->getType()) &&
           this->isStatic() == other->isStatic() &&
           this->isConst() == other->isConst();

}

bool ClassPropertyTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getType()->isEquivalentTo(otherType);
}

std::shared_ptr<TypeSignature> ClassPropertyTypeSignature::convertToVariableTypeSignature() {
    return this->getType();
}

void ClassPropertyTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("IS_STATIC - ", _isStatic);
    Logger::log("IS_CONST - ", _isConst);
    _accessModifier->print();
    _type->print();
    Logger::log("----------");
}