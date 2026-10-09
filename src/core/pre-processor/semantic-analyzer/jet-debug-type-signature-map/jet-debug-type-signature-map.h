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
// Created by Johny Georges on 2026-01-10.
//

#ifndef JETLANG_JET_DEBUG_TYPE_SIGNATURE_MAP_H
#define JETLANG_JET_DEBUG_TYPE_SIGNATURE_MAP_H

#include <optional>
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../../type-signature/types/function-vararg-type-signature-map/function-vararg-type-signature-map.h"

class JetDebugTypeSignatureMap {
public:
    static std::string getAssertDebugRefCountTypeSignatureKey();
    static std::string getAssertDebugStructRefCountTypeSignatureKey();
    static std::string getAssertDebugTupleRefCountTypeSignatureKey();
    static std::string getAssertDebugClassRefCountTypeSignatureKey();
    static std::string getAssertDebugLambdaRefCountTypeSignatureKey();
    static std::shared_ptr<FunctionTypeSignature> getAssertDebugRefCountTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getAssertDebugStructRefCountTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getAssertDebugTupleRefCountTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getAssertDebugClassRefCountTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getAssertDebugLambdaRefCountTypeSignature();
};

#endif //JETLANG_JET_DEBUG_TYPE_SIGNATURE_MAP_H
