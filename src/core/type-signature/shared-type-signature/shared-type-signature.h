//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_SHARED_TYPE_SIGNATURE_H
#define JETLANG_SHARED_TYPE_SIGNATURE_H

#include "../type-signature.h"

class SharedTypeSignature : public TypeSignature {
private:
    std::shared_ptr<TypeSignature> _underlyingType;
public:
    SharedTypeSignature();
    SharedTypeSignature(std::shared_ptr<TypeSignature> underlyingType);
    std::shared_ptr<TypeSignature> getUnderlyingType();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_SHARED_TYPE_SIGNATURE_H
