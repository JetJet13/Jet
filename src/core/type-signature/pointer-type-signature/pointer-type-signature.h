//
// Created by Johny Georges on 2024-11-21.
//

#ifndef JETLANG_POINTER_TYPE_SIGNATURE_H
#define JETLANG_POINTER_TYPE_SIGNATURE_H

#include "../type-signature.h"

class PointerTypeSignature : public TypeSignature {
private:
    std::shared_ptr<TypeSignature> _underlyingType;
public:
    PointerTypeSignature();
    PointerTypeSignature(std::shared_ptr<TypeSignature> underlyingType);
    std::shared_ptr<TypeSignature> getUnderlyingType();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_POINTER_TYPE_SIGNATURE_H
