// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature.h"

std::string TypeSignature::getModuleId() {
    return _moduleId;
}

std::string TypeSignature::getId() {
    return _id;
}

std::string TypeSignature::getKeyId() {
    return _keyId;
}

std::shared_ptr<TypeSignature> TypeSignature::markAsBuiltIn(BuiltInTypeSource builtInTypeSource) {
    _builtInTypeSource = builtInTypeSource;
    return shared_from_this();
}

std::shared_ptr<TypeSignature> TypeSignature::markAsDebug() {
    _isDebug = true;
    return shared_from_this();
}

std::shared_ptr<TypeSignature> TypeSignature::markAsGeneric() {
    _isGeneric = true;
    return shared_from_this();
}

bool TypeSignature::isBuiltIn() {
    return _builtInTypeSource.has_value();
}

bool TypeSignature::isDebug() {
    return _isDebug;
}

bool TypeSignature::isGeneric() {
    return _isGeneric;
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

std::shared_ptr<TypeSignature> TypeSignature::markAsPrototype() {
    _isPrototype = true;
    return shared_from_this();
}

bool TypeSignature::isPrototype() {
    return _isPrototype;
}

std::shared_ptr<TypeSignature> TypeSignature::setModuleId(std::string id) {
    _moduleId = id;
    return shared_from_this();
}

std::shared_ptr<TypeSignature> TypeSignature::setId(std::string id) {
    _id = id;
    return shared_from_this();
}

std::shared_ptr<TypeSignature> TypeSignature::setKeyId(std::string id) {
    _keyId = id;
    return shared_from_this();
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

void TypeSignature::copyFrom(std::shared_ptr<TypeSignature> otherType) {}

TypeSource TypeSignature::getTypeTarget() {
    return this->getTypeSource();
}

std::shared_ptr<TypeSignature> TypeSignature::getTargetTypeSignature() {
    return shared_from_this();
}

bool TypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->isEqualTo(otherType);
}

std::shared_ptr<TypeSignature> TypeSignature::convertToVariableTypeSignature() {
    return shared_from_this();
}