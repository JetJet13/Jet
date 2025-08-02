//
// Created by Johny Georges on 2025-08-01.
//

#include "function-vararg-type-signature-map.h"
#include <utility>

FunctionVarArgTypeSignatureMap::FunctionVarArgTypeSignatureMap(std::string functionName) {
    _functionName = functionName;
    _typeSignatureMap = std::unordered_map<std::string, InvocableTypeSignature*>();
    _typeSignatureKeyList = std::vector<std::string>();
}

std::string FunctionVarArgTypeSignatureMap::getFunctionName() {
    return _functionName;
}

void FunctionVarArgTypeSignatureMap::addFunctionVarArgTypeSignature(std::string key, InvocableTypeSignature* typeSignature) {
    _typeSignatureKeyList.push_back(key);
    _typeSignatureMap.insert(std::pair(key, typeSignature));
}

std::optional<std::pair<std::string, InvocableTypeSignature*>> FunctionVarArgTypeSignatureMap::findMatchFor(ArgumentListTypeSignature* argumentListTypeSignature) {
    for (const auto& key : _typeSignatureKeyList) {
        auto keyValue = _typeSignatureMap.find(key);
        if (keyValue->second->doArgumentsMatchParameters(argumentListTypeSignature)) {
            return std::pair(keyValue->first, keyValue->second);
        }
    }
    return {};
}