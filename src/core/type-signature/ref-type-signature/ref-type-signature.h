//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_REF_TYPE_SIGNATURE_H
#define JETLANG_REF_TYPE_SIGNATURE_H

#include "../type-signature.h"

class RefTypeSignature : public TypeSignature {
private:
    TypeSignature* _underlyingType;
public:
    RefTypeSignature();
    RefTypeSignature(TypeSignature* underlyingType);
    TypeSignature* getUnderlyingType();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_REF_TYPE_SIGNATURE_H
