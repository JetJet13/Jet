//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"

class BoolLiteralTypeSignature : public TypeSignature {
public:
    BoolLiteralTypeSignature();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H
