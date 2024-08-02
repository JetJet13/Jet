//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-array-type.h"

IRArrayType::IRArrayType(IRPointerType* arrayElementType) : IRType(arrayElementType->getPointerSourceType()) {
    _arrayElementType = arrayElementType;
}

IRPointerType* IRArrayType::getElementIRType() {
    return _arrayElementType;
}