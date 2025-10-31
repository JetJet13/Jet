//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature.h"

std::string TypeSignature::getId() {
    return _id;
}

TypeSignature* TypeSignature::markAsBuiltIn(BuiltInTypeSource builtInTypeSource) {
    _builtInTypeSource = builtInTypeSource;
    return this;
}

bool TypeSignature::isBuiltIn() {
    return _builtInTypeSource.has_value();
}

bool TypeSignature::builtInTypeSourceIs(BuiltInTypeSource builtInTypeSource) {
    if (!_builtInTypeSource) {
        return false;
    }
    return _builtInTypeSource.value() == builtInTypeSource;
}

bool TypeSignature::isOneOfBuiltInTypeSources(std::vector<BuiltInTypeSource> builtInTypeSources) {
    if (!_builtInTypeSource) {
        return false;
    }
    return std::find(
            builtInTypeSources.begin(),
            builtInTypeSources.end(),
            _builtInTypeSource.value()) != builtInTypeSources.end();
}

TypeSignature* TypeSignature::markAsPrototype() {
    _isPrototype = true;
    return this;
}

bool TypeSignature::isPrototype() {
    return _isPrototype;
}


TypeSignature* TypeSignature::setId(std::string id) {
    _id = id;
    return this;
}

bool TypeSignature::typeTargetIs(TypeSource other) {
    return this->getTypeTarget() == other;
}

bool TypeSignature::typeSourceIs(TypeSource other) {
    return this->getTypeSource() == other;
}

bool TypeSignature::isOneOf(std::vector<TypeSource> typeSources) {
    return std::find(
            typeSources.begin(),
            typeSources.end(),
            this->getTypeTarget()) != typeSources.end();
}

bool TypeSignature::isUnknown() {
    return this->getTypeTarget() == UNKNOWN_TYPE_SOURCE;
}

bool TypeSignature::isInvalid() {
    return this->getTypeTarget() == INVALID_TYPE_SOURCE;
}

bool TypeSignature::isVoid() {
    return this->getTypeTarget() == VOID_TYPE_SOURCE;
}

bool TypeSignature::isUnknownOrInvalidOrVoid() {
    return this->isUnknown() ||
           this->isInvalid() ||
           this->isVoid();
}

bool TypeSignature::isLiteral() {
    return false;
}

bool TypeSignature::isInvocable() {
    return false;
}

void TypeSignature::copyFrom(TypeSignature* otherType) {}

TypeSource TypeSignature::getTypeTarget() {
    return this->getTypeSource();
}

TypeSignature* TypeSignature::getTargetTypeSignature() {
    return this;
}

bool TypeSignature::isEquivalentTo(TypeSignature* otherType) {
    return this->isEqualTo(otherType);
}

TypeSignature* TypeSignature::convertToVariableTypeSignature() {
    return this;
}