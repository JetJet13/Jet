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
// Created by Johny Georges on 2025-08-01.
//

#ifndef JETLANG_FUNCTION_VARARG_TYPE_SIGNATURE_MAP_H
#define JETLANG_FUNCTION_VARARG_TYPE_SIGNATURE_MAP_H

#include <unordered_map>
#include "../../invocable-type-signature/invocable-type-signature.h"
#include "../../argument-list-type-signature/argument-list-type-signature.h"

class FunctionVarArgTypeSignatureMap {
private:
    std::string _functionName;
    std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>> _typeSignatureMap;
    std::vector<std::string> _typeSignatureKeyList;
public:
    FunctionVarArgTypeSignatureMap(std::string functionName);
    std::string getFunctionName();
    void addFunctionVarArgTypeSignature(std::string key, std::shared_ptr<InvocableTypeSignature> typeSignature);
    std::optional<std::pair<std::string, std::shared_ptr<InvocableTypeSignature>>> findMatchFor(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature);
    std::string toString();
};

#endif //JETLANG_FUNCTION_VARARG_TYPE_SIGNATURE_MAP_H
