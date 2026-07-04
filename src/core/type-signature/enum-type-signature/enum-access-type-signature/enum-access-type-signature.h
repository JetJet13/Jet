//
// Created by Johny Georges on 2024-05-17.
//

#ifndef JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H
#define JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../enum-type-signature.h"

class EnumAccessTypeSignature : public TypeSignature {
private:
    std::shared_ptr<EnumTypeSignature> _enum;
    std::string _key;
public:
    EnumAccessTypeSignature(std::shared_ptr<EnumTypeSignature> enumTypeSignature, std::string key);
    std::shared_ptr<EnumTypeSignature> getEnum();
    std::string getKey();
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H
