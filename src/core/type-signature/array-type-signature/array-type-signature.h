//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_ARRAY_TYPE_SIGNATURE_H
#define JETLANG_ARRAY_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../literal-type-signature/int-literal-type-signature.h"

class ArrayTypeSignature : public TypeSignature {
private:
    TypeSignature* _elementType;
    IntLiteralTypeSignature* _size;
public:
    ArrayTypeSignature(TypeSignature* elementType, IntLiteralTypeSignature* size);
    TypeSignature* getElementType();
    IntLiteralTypeSignature* getSize();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_ARRAY_TYPE_SIGNATURE_H
