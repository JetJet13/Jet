//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_TYPE_SIGNATURE_H
#define JETLANG_MODULE_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class ModuleTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _keyValuePairs;
public:
    ModuleTypeSignature();
    ModuleTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs);
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<TypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<TypeSignature> getTypeSignatureAtIndex(uint64_t index) override;
    void addKeyValuePair(std::string key, std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_MODULE_TYPE_SIGNATURE_H
