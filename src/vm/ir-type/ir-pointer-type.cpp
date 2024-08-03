//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-pointer-type.h"

IRPointerType::IRPointerType(llvm::PointerType* type, IRType* sourceType) : IRType(type) {
    _type = type;
    _sourceType = sourceType;
}

IRType* IRPointerType::getPointerSourceIRType() {
    return _sourceType;
}

void IRPointerType::setSourceType(IRType* type) {
    _sourceType = type;
}