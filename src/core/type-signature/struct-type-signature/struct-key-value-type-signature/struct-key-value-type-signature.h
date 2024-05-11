//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_STRUCT_KEY_VALUE_TYPE_SIGNATURE_H
#define JETLANG_STRUCT_KEY_VALUE_TYPE_SIGNATURE_H

#include <string>
#include "../../type-signature.h"

class StructKeyValueTypeSignature : public TypeSignature {
private:
    std::string _key;
    TypeSignature* _value;
public:
    StructKeyValueTypeSignature(std::string key, TypeSignature* value);
    std::string getKey();
    TypeSignature* getValue();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_STRUCT_KEY_VALUE_TYPE_SIGNATURE_H
