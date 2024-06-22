//
// Created by Johny Georges on 2024-06-19.
//

#include "ir-type.h"

IRType::IRType(llvm::Type* type) {
    _type = type;
}

llvm::Type* IRType::getType() {
    return _type;
}

bool IRType::isCharType() {
    return _type->isIntegerTy(8);
}

bool IRType::isIntegerType() {
    return _type->isIntegerTy();
}

bool IRType::isFloatType() {
    return _type->isFloatTy();
}

bool IRType::isArrayType() {
    return _type->isArrayTy();
}

bool IRType::isEqual(IRType* otherValue) {
    if (this->isIntegerType() && otherValue->isIntegerType()) {
        return this->getType()->getIntegerBitWidth() == otherValue->getType()->getIntegerBitWidth();
    }

    if (this->isFloatType() && otherValue->isFloatType()) {
        return this->getType()->getFPMantissaWidth() == otherValue->getType()->getFPMantissaWidth();
    }

    if (this->isArrayType() && otherValue->isArrayType()) {
        auto elementType = new IRType(this->getType()->getArrayElementType());
        auto otherElementType = new IRType(otherValue->getType()->getArrayElementType());
        return this->getType()->getArrayNumElements() == otherValue->getType()->getArrayNumElements() &&
                elementType->isEqual(otherElementType);
    }

    return false;
}

bool IRType::isNotEqual(IRType* otherValue) {
    return !this->isEqual(otherValue);
}

bool IRType::isLessThan(IRType* otherValue) {
    if (this->isIntegerType() && otherValue->isIntegerType()) {
        return this->getType()->getIntegerBitWidth() < otherValue->getType()->getIntegerBitWidth();
    }

    if (this->isFloatType() && otherValue->isFloatType()) {
        return this->getType()->getFPMantissaWidth() < otherValue->getType()->getFPMantissaWidth();
    }

    if (this->isArrayType() && otherValue->isArrayType()) {
        return this->getType()->getArrayNumElements() < otherValue->getType()->getArrayNumElements();
    }

    return false;
}

bool IRType::isLessThanOrEqual(IRType* otherValue) {
    return this->isEqual(otherValue) || this->isLessThan(otherValue);
}

bool IRType::isGreaterThan(IRType* otherValue) {
    if (this->isIntegerType() && otherValue->isIntegerType()) {
        return this->getType()->getIntegerBitWidth() > otherValue->getType()->getIntegerBitWidth();
    }

    if (this->isFloatType() && otherValue->isFloatType()) {
        return this->getType()->getFPMantissaWidth() > otherValue->getType()->getFPMantissaWidth();
    }

    if (this->isArrayType() && otherValue->isArrayType()) {
        return this->getType()->getArrayNumElements() > otherValue->getType()->getArrayNumElements();
    }

    return false;
}

bool IRType::isGreaterThanOrEqual(IRType* otherValue) {
    return this->isEqual(otherValue) || this->isGreaterThan(otherValue);
}
