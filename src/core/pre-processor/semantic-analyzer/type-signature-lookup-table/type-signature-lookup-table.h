//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
#define JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H

#include <unordered_map>
#include "../../../type-signature/type-signature.h"
#include "../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/float-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/char-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/string-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../type-signature/types/function-vararg-type-signature-map/function-vararg-type-signature-map.h"

class TypeSignatureLookupTable {
private:
    std::unordered_map<std::string, TypeSignature*> _typeSignatureLookupTable;
    std::unordered_map<std::string, TypeSignature*>* _globalTypeSignatureLookupTable;
    std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* _globalFunctionOverrideLookupTable;
    std::optional<TypeSignatureLookupTable*> _outerScope;
public:
    explicit TypeSignatureLookupTable(std::optional<TypeSignatureLookupTable*> outerScope = {});
    TypeSignatureLookupTable* insert(std::string key, TypeSignature* typeSignature);
    TypeSignatureLookupTable* insertGlobal(std::string key, TypeSignature* typeSignature);
    TypeSignatureLookupTable* insertGlobalFunctionOverride(FunctionVarArgTypeSignatureMap* functionOverrideTypeSignatureMap);
    TypeSignature* find(std::string key);
    TypeSignature* findGlobal(std::string key);
    std::optional<FunctionVarArgTypeSignatureMap*> findGlobalFunctionOverride(std::string key);
    std::unordered_map<std::string, TypeSignature*> getLookupTable();
    std::unordered_map<std::string, TypeSignature*>* getGlobalScope();
    std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* getGlobalOverrideScope();
    void inheritGlobalScope(TypeSignatureLookupTable* otherScope);
    void dump();
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
