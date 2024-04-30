//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_ARRAY_TYPE_H
#define JETLANG_ARRAY_TYPE_H

#include "base-type.h"

class ArrayType : public BaseType {
private:
    BaseType* _elementType;
    int _size;
public:
    ArrayType(BaseType* elementType, int size);
    BaseType* getElementType();
    int getSize();
    TypeSource getTypeSource() override;
    bool isEqualTo(BaseType *otherType) override;
};

#endif //JETLANG_ARRAY_TYPE_H
