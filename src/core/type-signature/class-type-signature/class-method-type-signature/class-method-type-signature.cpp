//
// Created by Johny Georges on 2024-05-03.
//

#include "class-method-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ClassMethodTypeSignature::ClassMethodTypeSignature(AccessModifierTypeSignature* accessModifier, ParameterListTypeSignature* parameterList, bool isStatic, std::optional<TypeSignature*> returnType) {
    _accessModifier = accessModifier;
    _parameterList = parameterList;
    _isStatic = isStatic;
    _returnType = returnType;
}

bool ClassMethodTypeSignature::isStatic() {
    return _isStatic;
}

AccessModifierTypeSignature* ClassMethodTypeSignature::getAccessModifier() {
    return _accessModifier;
}

ParameterListTypeSignature* ClassMethodTypeSignature::getParameters() {
    return _parameterList;
}

std::optional<TypeSignature*> ClassMethodTypeSignature::getReturnType() {
    return _returnType;
}

std::string ClassMethodTypeSignature::toString() {
    return "CLASS_METHOD_TYPE_SIGNATURE";
}

TypeSource ClassMethodTypeSignature::getTypeSource() {
    return CLASS_METHOD_TYPE_SOURCE;
}

bool ClassMethodTypeSignature::isEqualTo(TypeSignature *otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = (ClassMethodTypeSignature*)otherType;
    if (!_returnType.has_value() && other->getReturnType().has_value() ||
        _returnType.has_value() && !other->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && other->getReturnType().has_value() &&
        !_returnType.value()->isEqualTo(other->getReturnType().value())) {
        return false;
    }

    return this->getAccessModifier()->isEqualTo(other->getAccessModifier()) &&
    this->isStatic() == other->isStatic() &&
    this->getParameters()->isEqualTo(other->getParameters());

}

void ClassMethodTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("IS_STATIC - ", _isStatic);
    _accessModifier->print();
    _parameterList->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    Logger::log("----------");
}