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
    std::unordered_map<std::string, InvocableTypeSignature*> _typeSignatureMap;
    std::vector<std::string> _typeSignatureKeyList;
public:
    FunctionVarArgTypeSignatureMap(std::string functionName);
    std::string getFunctionName();
    void addFunctionVarArgTypeSignature(std::string key, InvocableTypeSignature* typeSignature);
    std::optional<std::pair<std::string, InvocableTypeSignature*>> findMatchFor(ArgumentListTypeSignature* argumentListTypeSignature);
};

#endif //JETLANG_FUNCTION_VARARG_TYPE_SIGNATURE_MAP_H
