//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_ARRAY_TYPE_SIGNATURE_H
#define JETLANG_ARRAY_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../literal-type-signature/int-literal-type-signature.h"

class ArrayTypeSignature : public TypeSignature {
private:
    std::shared_ptr<TypeSignature> _elementType;
public:
    ArrayTypeSignature();
    ArrayTypeSignature(std::shared_ptr<TypeSignature> elementType);
    std::shared_ptr<TypeSignature> getElementType();
    void setElementType(std::shared_ptr<TypeSignature> elementType);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ARRAY_TYPE_SIGNATURE_H
