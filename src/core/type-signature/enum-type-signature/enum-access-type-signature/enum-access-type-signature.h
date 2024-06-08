//
// Created by Johny Georges on 2024-05-17.
//

#ifndef JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H
#define JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../enum-type-signature.h"

class EnumAccessTypeSignature : public TypeSignature {
private:
    EnumTypeSignature* _enum;
    std::string _key;
public:
    EnumAccessTypeSignature(EnumTypeSignature* enumTypeSignature, std::string key);
    EnumTypeSignature* getEnum();
    std::string getKey();
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    bool isEquivalentTo(TypeSignature* otherType) override;
    bool isEqualTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H
