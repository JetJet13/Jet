//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
#define JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H

#include <unordered_map>
#include "../type-signature-generator/types/type-signature.h"

class TypeSignatureLookupTable {
private:
    std::unordered_map<std::string, TypeSignature*> _typeSignatureLookupTable;
    void initLiteralTypeSignatures();
public:
    TypeSignatureLookupTable();
    TypeSignatureLookupTable* insert(std::string key, TypeSignature* typeSignature);
    std::optional<TypeSignature*> find(std::string key);
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
