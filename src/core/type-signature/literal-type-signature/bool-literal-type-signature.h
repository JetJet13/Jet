//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"
#include "literal-type-signature.h"

class BoolLiteralTypeSignature : public LiteralTypeSignature {
public:
    LiteralTypeSignature* clone() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(TypeSignature *otherType) override;
};

#endif //JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H
