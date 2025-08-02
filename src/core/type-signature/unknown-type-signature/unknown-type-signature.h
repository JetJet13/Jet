//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_UNKNOWN_TYPE_SIGNATURE_H
#define JETLANG_UNKNOWN_TYPE_SIGNATURE_H

#include "../type-signature.h"

class UnknownTypeSignature : public TypeSignature {
public:
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};


#endif //JETLANG_UNKNOWN_TYPE_SIGNATURE_H
