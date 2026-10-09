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

#include "function-vararg-type-signature-map.h"
#include <utility>

FunctionVarArgTypeSignatureMap::FunctionVarArgTypeSignatureMap(std::string functionName) {
    _functionName = functionName;
    _typeSignatureMap = std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>();
    _typeSignatureKeyList = std::vector<std::string>();
}

std::string FunctionVarArgTypeSignatureMap::getFunctionName() {
    return _functionName;
}

void FunctionVarArgTypeSignatureMap::addFunctionVarArgTypeSignature(std::string key, std::shared_ptr<InvocableTypeSignature> typeSignature) {
    _typeSignatureKeyList.push_back(key);
    _typeSignatureMap.insert(std::pair(key, typeSignature));
}

std::optional<std::pair<std::string, std::shared_ptr<InvocableTypeSignature>>> FunctionVarArgTypeSignatureMap::findMatchFor(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    for (const auto& key : _typeSignatureKeyList) {
        auto keyValue = _typeSignatureMap.find(key);
        if (keyValue->second->doArgumentsMatchParameters(argumentListTypeSignature)) {
            return std::pair(keyValue->first, keyValue->second);
        }
    }
    return {};
}

std::string FunctionVarArgTypeSignatureMap::toString() {
    return "FUNCTION_VAR_ARG_TYPE_SIGNATURE";
}