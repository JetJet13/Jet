//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_STRUCT_TYPE_SIGNATURE_H
#define JETLANG_STRUCT_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../types/type-signature-map/type-signature-map.h"
#include "struct-key-value-type-signature/struct-key-value-type-signature.h"

class StructTypeSignature : public TypeSignature {
private:
    TypeSignatureMap<TypeSignature> _keyValuePairs;
public:
    StructTypeSignature();
    StructTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs);
    TypeSignatureMap<TypeSignature>* getKeyValuePairs();
    TypeSignature* getTypeSignatureForKey(std::string key);
    void addKeyValuePair(std::string key, TypeSignature* typeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_STRUCT_TYPE_SIGNATURE_H
