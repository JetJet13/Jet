//
// Created by Johny Georges on 2024-08-09.
//

#include "ir-array-type.h"
#include "../../shared/utils/logger/logger.h"

IRArrayType::IRArrayType(llvm::ArrayType* type, IRType* arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
}

llvm::ArrayType* IRArrayType::getType() {
    return _type;
}

IRType* IRArrayType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayType::getElementType() {
    return _arrayElementType->getType();
}

uint64_t IRArrayType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return _type->getNumElements() * _arrayElementType->getSizeInBytes();
}

void IRArrayType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _arrayElementType->setAlignmentOverride(alignmentOverride);
}


llvm::Align IRArrayType::getAlignment() {
    return this->getElementIRType()->getAlignment();
}

bool IRArrayType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRArrayType::isArrayType() {
    return true;
}

void IRArrayType::print() {
    Logger::log("IR ARRAY TYPE");
    _type->print(llvm::outs());
}