//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_INT_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_INT_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"
#include "literal-type-signature.h"

class IntLiteralTypeSignature : public LiteralTypeSignature {
public:
    std::string toString() override;
    TypeSource getTypeSource() override;
};

#endif //JETLANG_INT_LITERAL_TYPE_SIGNATURE_H
