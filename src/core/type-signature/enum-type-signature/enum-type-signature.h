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
    LiteralTypeSignature* _type;
protected:
    TypeSignatureMap<LiteralTypeSignature> _keyValuePairs;
public:
    EnumTypeSignature();
    explicit EnumTypeSignature(LiteralTypeSignature* type);
    EnumTypeSignature(LiteralTypeSignature* type, TypeSignatureMap<LiteralTypeSignature> keyValuePairs);
    EnumTypeSignature* setKeyId(std::string id) override;
    TypeSignatureMap<LiteralTypeSignature>* getKeyValuePairs() override;
    LiteralTypeSignature* getTypeSignatureForKey(std::string key) override;
    LiteralTypeSignature* getTypeSignatureAtIndex(unsigned long index) override;
    LiteralTypeSignature* getType();
    void setType(LiteralTypeSignature* type);
    bool hasKey(std::string key);
    void addKey(std::string key);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    bool isEqualTo(TypeSignature *otherType) override;
    void copyFrom(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_H
