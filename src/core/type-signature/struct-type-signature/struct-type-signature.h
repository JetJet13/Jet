//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_STRUCT_TYPE_SIGNATURE_H
#define JETLANG_STRUCT_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class StructTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _keyValuePairs;
public:
    StructTypeSignature();
    StructTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs);
    bool isEmpty();
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<TypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<TypeSignature> getTypeSignatureAtIndex(unsigned long index) override;
    void addKeyValuePair(std::string key, std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_STRUCT_TYPE_SIGNATURE_H
