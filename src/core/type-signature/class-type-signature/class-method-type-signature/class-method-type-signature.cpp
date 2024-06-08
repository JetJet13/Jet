//
// Created by Johny Georges on 2024-05-03.
//

#include "class-method-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../void-type-signature/void-type-signature.h"

ClassMethodTypeSignature::ClassMethodTypeSignature() {
    _accessModifier = new AccessModifierTypeSignature();
    _parameterList = new ParameterListTypeSignature();
    _isStatic = false;
    _returnType = new VoidTypeSignature();
}

ClassMethodTypeSignature::ClassMethodTypeSignature(AccessModifierTypeSignature* accessModifier, ParameterListTypeSignature* parameterList, bool isStatic, std::optional<TypeSignature*> returnType) {
    _accessModifier = accessModifier;
    _parameterList = parameterList;
    _isStatic = isStatic;
    if (returnType) {
        _returnType = returnType.value();
    } else {
        _returnType = new VoidTypeSignature();
    }
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

std::vector<TypeSignature*>* ClassMethodTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

TypeSignature* ClassMethodTypeSignature::getReturnType() {
    return _returnType;
}

void ClassMethodTypeSignature::setReturnType(TypeSignature* returnType) {
    _returnType = returnType;
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
    return this->getAccessModifier()->isEqualTo(other->getAccessModifier()) &&
           this->isStatic() == other->isStatic() &&
           this->getParameters()->isEqualTo(other->getParameters()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}

void ClassMethodTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("IS_STATIC - ", _isStatic);
    _accessModifier->print();
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}