//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"

class LiteralTypeSignature : public TypeSignature {
public:
    bool isLiteral() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_H
