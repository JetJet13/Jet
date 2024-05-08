//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_STRING_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_STRING_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"

class StringLiteralTypeSignature : public TypeSignature {
public:
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_STRING_LITERAL_TYPE_SIGNATURE_H
