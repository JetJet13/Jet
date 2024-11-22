//
// Created by Johny Georges on 2024-11-21.
//

#ifndef JETLANG_POINTER_TYPE_SIGNATURE_H
#define JETLANG_POINTER_TYPE_SIGNATURE_H

#include "../type-signature.h"

class PointerTypeSignature : public TypeSignature {
private:
    TypeSignature* _underlyingType;
public:
    PointerTypeSignature(TypeSignature* underlyingType);
    TypeSignature* getUnderlyingType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_POINTER_TYPE_SIGNATURE_H
