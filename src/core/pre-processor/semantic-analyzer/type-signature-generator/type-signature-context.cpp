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
// Created by Johny Georges on 2026-03-19.
//

#include "type-signature-context.h"

TypeSignatureContext::TypeSignatureContext() {
    _typeSignature = {};
    _typeSignatures = {};
}

TypeSignatureContext::TypeSignatureContext(std::optional<std::shared_ptr<TypeSignature>> typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignatureContext::TypeSignatureContext(std::optional<std::vector<std::shared_ptr<TypeSignature>>*> typeSignatures) {
    _typeSignatures = typeSignatures;
}

std::optional<std::shared_ptr<TypeSignature>> TypeSignatureContext::getTypeSignature() {
    return _typeSignature;
}

std::optional<std::vector<std::shared_ptr<TypeSignature>>*> TypeSignatureContext::getTypeSignatures() {
    return _typeSignatures;
}