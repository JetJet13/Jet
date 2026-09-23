//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_INTERFACE_TYPE_SIGNATURE_H
#define JETLANG_INTERFACE_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class InterfaceTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _properties;
public:
    InterfaceTypeSignature();
    InterfaceTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs);
    bool isEmpty();
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<TypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<TypeSignature> getTypeSignatureAtIndex(uint64_t index) override;
    void addProperty(std::string key, std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_INTERFACE_TYPE_SIGNATURE_H
