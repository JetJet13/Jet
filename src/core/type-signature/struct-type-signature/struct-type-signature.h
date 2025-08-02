//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_STRUCT_TYPE_SIGNATURE_H
#define JETLANG_STRUCT_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class StructTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<TypeSignature> _keyValuePairs;
public:
    StructTypeSignature();
    StructTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs);
    bool isEmpty();
    TypeSignatureMap<TypeSignature>* getKeyValuePairs() override;
    TypeSignature* getTypeSignatureForKey(std::string key) override;
    TypeSignature* getTypeSignatureAtIndex(unsigned long index) override;
    void addKeyValuePair(std::string key, TypeSignature* typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_STRUCT_TYPE_SIGNATURE_H
