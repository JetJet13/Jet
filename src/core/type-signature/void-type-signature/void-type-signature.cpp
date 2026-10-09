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
// Created by Johny Georges on 2024-05-07.
//

#include "void-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


std::string VoidTypeSignature::toDetailString() {
    return "jet.void";
}

std::string VoidTypeSignature::toString() {
    return "VOID_TYPE_SIGNATURE";
}

TypeSource VoidTypeSignature::getTypeSource() {
    return VOID_TYPE_SOURCE;
}

bool VoidTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void VoidTypeSignature::print() {
    Logger::log(this->toString());
}