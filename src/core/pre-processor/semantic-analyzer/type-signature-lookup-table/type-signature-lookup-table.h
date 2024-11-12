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

class TypeSignatureLookupTable {
private:
    std::unordered_map<std::string, TypeSignature*> _typeSignatureLookupTable;
    std::optional<TypeSignatureLookupTable*> _outerScope;
public:
    explicit TypeSignatureLookupTable(std::optional<TypeSignatureLookupTable*> outerScope = {});
    TypeSignatureLookupTable* insert(std::string key, TypeSignature* typeSignature);
    TypeSignature* find(std::string key);
    std::unordered_map<std::string, TypeSignature*> getLookupTable();
    void dump();
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
