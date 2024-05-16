//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_H
#define JETLANG_ENUM_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "../../lexeme/lexeme.h"
#include "../procedure-type-signature/procedure-type-signature.h"
#include "../types/type-signature-map/type-signature-map.h"
#include "../literal-type-signature/literal-type-signature.h"

class EnumTypeSignature : public TypeSignature {
private:
    LiteralTypeSignature* _type;
    TypeSignatureMap<LiteralTypeSignature> _keyValuePairs;
public:
    EnumTypeSignature();
    EnumTypeSignature(LiteralTypeSignature* type);
    TypeSignatureMap<LiteralTypeSignature>* getKeyValuePairs();
    LiteralTypeSignature* getType();
    bool hasKey(std::string key);
    void addKey(std::string key);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void copyFrom(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_H
