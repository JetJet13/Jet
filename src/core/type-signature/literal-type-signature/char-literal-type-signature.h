//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_CHAR_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_CHAR_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"

class CharLiteralTypeSignature : public TypeSignature {
public:
    CharLiteralTypeSignature();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CHAR_LITERAL_TYPE_SIGNATURE_H
