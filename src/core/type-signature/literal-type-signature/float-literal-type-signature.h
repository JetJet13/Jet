//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_FLOAT_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_FLOAT_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"
#include "literal-type-signature.h"

class FloatLiteralTypeSignature : public LiteralTypeSignature {
public:
    std::shared_ptr<LiteralTypeSignature> clone() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
};


#endif //JETLANG_FLOAT_LITERAL_TYPE_SIGNATURE_H
