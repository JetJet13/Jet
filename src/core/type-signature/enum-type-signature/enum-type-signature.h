//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_H
#define JETLANG_ENUM_TYPE_SIGNATURE_H

#include "../literal-type-signature/types/literal-type.h"
#include "../../lexeme/lexeme.h"
#include "../types/type-signature-map/type-signature-map.h"
#include "../literal-type-signature/literal-type-signature.h"
#include "../aggregate-type-signature.h"

class EnumTypeSignature : public AggregateTypeSignature<LiteralTypeSignature> {
private:
    std::shared_ptr<LiteralTypeSignature> _type;
protected:
    TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>> _keyValuePairs;
public:
    EnumTypeSignature();
    explicit EnumTypeSignature(std::shared_ptr<LiteralTypeSignature> type);
    EnumTypeSignature(std::shared_ptr<LiteralTypeSignature> type, TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>> keyValuePairs);
    std::shared_ptr<TypeSignature> setKeyId(std::string id) override;
    TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<LiteralTypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<LiteralTypeSignature> getTypeSignatureAtIndex(unsigned long index) override;
    std::shared_ptr<LiteralTypeSignature> getType();
    void setType(std::shared_ptr<LiteralTypeSignature> type);
    bool hasKey(std::string key);
    void addKey(std::string key);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void copyFrom(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_H
