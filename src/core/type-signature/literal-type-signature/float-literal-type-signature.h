//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_FLOAT_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_FLOAT_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"

class FloatLiteralTypeSignature : public TypeSignature {
public:
    FloatLiteralTypeSignature();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};


#endif //JETLANG_FLOAT_LITERAL_TYPE_SIGNATURE_H
