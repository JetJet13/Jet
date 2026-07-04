//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_REF_TYPE_SIGNATURE_H
#define JETLANG_REF_TYPE_SIGNATURE_H

#include "../type-signature.h"

class RefTypeSignature : public TypeSignature {
private:
    std::shared_ptr<TypeSignature> _underlyingType;
public:
    RefTypeSignature();
    RefTypeSignature(std::shared_ptr<TypeSignature> underlyingType);
    std::shared_ptr<TypeSignature> getUnderlyingType();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_REF_TYPE_SIGNATURE_H
