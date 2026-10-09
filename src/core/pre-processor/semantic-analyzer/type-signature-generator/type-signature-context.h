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

#ifndef JETLANG_TYPE_SIGNATURE_CONTEXT_H
#define JETLANG_TYPE_SIGNATURE_CONTEXT_H

#include "../../../type-signature/type-signature.h"

class TypeSignatureContext {
private:
    std::optional<std::shared_ptr<TypeSignature>> _typeSignature;
    std::optional<std::vector<std::shared_ptr<TypeSignature>>*> _typeSignatures;
public:
    TypeSignatureContext();
    TypeSignatureContext(std::optional<std::shared_ptr<TypeSignature>> typeSignature);
    TypeSignatureContext(std::optional<std::vector<std::shared_ptr<TypeSignature>>*> typeSignatures);
    std::optional<std::shared_ptr<TypeSignature>> getTypeSignature();
    std::optional<std::vector<std::shared_ptr<TypeSignature>>*> getTypeSignatures();
};

#endif //JETLANG_TYPE_SIGNATURE_CONTEXT_H
