//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_ARRAY_TYPE_SIGNATURE_H
#define JETLANG_ARRAY_TYPE_SIGNATURE_H

#include "type-signature.h"

class ArrayTypeSignature : public TypeSignature {
private:
    TypeSignature* _elementType;
    int _size;
public:
    ArrayTypeSignature(TypeSignature* elementType, int size);
    TypeSignature* getElementType();
    int getSize();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_ARRAY_TYPE_SIGNATURE_H
