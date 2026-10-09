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
// Created by Johny Georges on 2024-05-03.
//

#include "parameter-list-item-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../struct-type-signature/struct-type-signature.h"

std::shared_ptr<ParameterListItemTypeSignature> ParameterListItemTypeSignature::createScopeParameter(std::optional<std::shared_ptr<LambdaScopeTypeSignature>> scopeTypeSignature) {
    return std::make_shared<ParameterListItemTypeSignature>("jet.lambda.scope", scopeTypeSignature.value_or(std::make_shared<LambdaScopeTypeSignature>()));
}

std::shared_ptr<ParameterListItemTypeSignature> ParameterListItemTypeSignature::createClassScopeParameter(std::optional<std::shared_ptr<PointerTypeSignature>> scopeTypeSignature) {
    return std::make_shared<ParameterListItemTypeSignature>("jet.class.scope", scopeTypeSignature.value_or(std::make_shared<PointerTypeSignature>(std::make_shared<StructTypeSignature>())));
}

ParameterListItemTypeSignature::ParameterListItemTypeSignature(std::string name, std::shared_ptr<TypeSignature> type) {
    _name = name;
    _type = type;
}

std::string ParameterListItemTypeSignature::getName() {
    return _name;
}

std::shared_ptr<TypeSignature> ParameterListItemTypeSignature::getTypeSignature() {
    return _type;
}

void ParameterListItemTypeSignature::setType(std::shared_ptr<TypeSignature> typeSignature) {
    _type = typeSignature;
}

std::string ParameterListItemTypeSignature::toDetailString() {
    return _type->toDetailString();
}

std::string ParameterListItemTypeSignature::toString() {
    return "PARAMETER_ITEM_TYPE_SIGNATURE";
}

TypeSource ParameterListItemTypeSignature::getTypeSource() {
    return PARAMETER_ITEM_TYPE_SOURCE;
}

bool ParameterListItemTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ParameterListItemTypeSignature>(otherType);
    return this->getName() == other->getName() &&
            this->getTypeSignature()->isEqualTo(other->getTypeSignature());
}

bool ParameterListItemTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return _type->isEquivalentTo(otherType);
}

void ParameterListItemTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _type->print();
    Logger::log("----------");
}