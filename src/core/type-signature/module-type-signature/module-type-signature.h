//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_TYPE_SIGNATURE_H
#define JETLANG_MODULE_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class ModuleTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<TypeSignature> _keyValuePairs;
public:
    ModuleTypeSignature();
    ModuleTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs);
    TypeSignatureMap<TypeSignature>* getKeyValuePairs() override;
    TypeSignature* getTypeSignatureForKey(std::string key) override;
    TypeSignature* getTypeSignatureAtIndex(unsigned long index) override;
    void addKeyValuePair(std::string key, TypeSignature* typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_MODULE_TYPE_SIGNATURE_H
