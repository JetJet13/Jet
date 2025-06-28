//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_INTERFACE_TYPE_SIGNATURE_H
#define JETLANG_INTERFACE_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class InterfaceTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<TypeSignature> _properties;
public:
    InterfaceTypeSignature();
    InterfaceTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs);
    bool isEmpty();
    TypeSignatureMap<TypeSignature>* getKeyValuePairs() override;
    TypeSignature* getTypeSignatureForKey(std::string key) override;
    TypeSignature* getTypeSignatureAtIndex(unsigned long index) override;
    void addProperty(std::string key, TypeSignature* typeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_INTERFACE_TYPE_SIGNATURE_H
