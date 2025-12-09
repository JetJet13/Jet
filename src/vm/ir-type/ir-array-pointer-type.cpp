//
// Created by Johny Georges on 2024-08-08.
//

#include "ir-array-pointer-type.h"
#include "../../shared/utils/logger/logger.h"

IRArrayPointerType::IRArrayPointerType(llvm::StructType* type, IRType* arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
    _numElementsIndex = 0;
    _depthIndex = 1;
    _allocIndex = 2;
}

llvm::StructType* IRArrayPointerType::getType() {
    return _type;
}

unsigned int IRArrayPointerType::getNumElementsIndex() const {
    return _numElementsIndex;
}

unsigned int IRArrayPointerType::getDepthIndex() const {
    return _depthIndex;
}

unsigned int IRArrayPointerType::getAllocIndex() const {
    return _allocIndex;
}

llvm::Type* IRArrayPointerType::getNumElementsType() {
    return _type->getStructElementType(0);
}

llvm::PointerType* IRArrayPointerType::getAllocType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(2));
}

IRType* IRArrayPointerType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayPointerType::getElementType() {
    return _arrayElementType->getType();
}

unsigned long IRArrayPointerType::getDepth() {
    auto depth = 1;
    auto irType = _arrayElementType;
    while (irType->isArrayPointerType()) {
        depth++;
        auto arrayPointerType = (IRArrayPointerType*)irType;
        irType = arrayPointerType->getElementIRType();
    }
    return depth;
}

uint64_t IRArrayPointerType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 24;
}

void IRArrayPointerType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _arrayElementType->setAlignmentOverride(alignmentOverride);
}

bool IRArrayPointerType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRArrayPointerType::isArrayPointerType() {
    return true;
}

IRArrayPointerType* IRArrayPointerType::clone() {
    auto elementClone = _arrayElementType->clone();
    auto clone = new IRArrayPointerType(_type, elementClone);
    this->initClone(clone);
    return clone;
}

void IRArrayPointerType::print() {
    Logger::log("IR ARRAY POINTER TYPE");
    _type->print(llvm::outs());
}