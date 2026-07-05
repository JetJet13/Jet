//
// Created by Johny Georges on 2024-08-09.
//

#include "ir-array-type.h"
#include "../../shared/utils/logger/logger.h"

IRArrayType::IRArrayType(llvm::ArrayType* type, std::shared_ptr<IRType> arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
}

llvm::ArrayType* IRArrayType::getType() {
    return _type;
}

std::shared_ptr<IRType> IRArrayType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayType::getElementType() {
    return _arrayElementType->getType();
}

uint64_t IRArrayType::getSize() {
    return _type->getNumElements();
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

std::shared_ptr<IRType> IRArrayType::clone() {
    auto elementClone = _arrayElementType->clone();
    auto clone = std::make_shared<IRArrayType>(_type, elementClone);
    this->initClone(clone);
    return clone;
}

void IRArrayType::print() {
    Logger::log("IR ARRAY TYPE");
    _type->print(llvm::outs());
}