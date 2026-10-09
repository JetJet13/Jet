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
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_ARRAY_PROTOTYPE_TYPE_SIGNATURE_MAP_H
#define JETLANG_ARRAY_PROTOTYPE_TYPE_SIGNATURE_MAP_H

#include <vector>
#include "../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

class ArrayPrototypeTypeSignatureMap {
public:
    std::optional<std::shared_ptr<FunctionTypeSignature>> find(std::string id, std::shared_ptr<TypeSignature> elementType);
};

#endif //JETLANG_ARRAY_PROTOTYPE_TYPE_SIGNATURE_MAP_H
