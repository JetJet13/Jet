//
// Created by Johny Georges on 2024-06-19.
//

#include <llvm/IR/Type.h>
#include "ir-type.h"
#include "../ir-nodes/ir-instruction-node.h"
#include "../../shared/utils/logger/logger.h"

IRType::IRType(llvm::Type* type) {
    _type = type;
    _alignmentOverride = {};
}

llvm::Type* IRType::getType() {
    return _type;
}

IRType* IRType::getSourceType() {
    return this;
}

uint64_t IRType::getSizeInBytes() {
    if (_alignmentOverride) {
        return _alignmentOverride.value().value();
    } else if (this->isCharType() || this->isBoolType()) {
        return 1;
    } else if (this->isIntegerType() || this->isPointerType() || this->isFloatType() || this->isInteger64Type()) {
        return 8;
    } else {
        return 0;
    }
}

void IRType::setValue(IRInstructionNode* value) {
    _value = value;
}

IRInstructionNode* IRType::getValue() {
    if (!_value) {
        throw std::logic_error("ir type has no value");
    }
    return _value.value();
}

void IRType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
}

llvm::Align IRType::getAlignment() {
    if (_alignmentOverride) {
        return _alignmentOverride.value();
    }

    if (this->isCharType() || this->isBoolType()) {
        return llvm::Align(1);
    }

    if (this->isIntegerType()) {
        return llvm::Align(8);
    }

    if (this->isFloatType()) {
        return llvm::Align(8);
    }

    if (this->isArrayPointerType() || this->isTypeValueType() || this->isRefType()) {
        return llvm::Align(8);
    }

    return llvm::Align(1);
}

bool IRType::hasValue() {
    return _value.has_value();
}

bool IRType::isCharType() {
    return _type->isIntegerTy(8);
}

bool IRType::isIntegerType() {
    return _type->isIntegerTy(64);
}

bool IRType::isInteger64Type() {
    return _type->isIntegerTy(64);
}

bool IRType::isFloatType() {
    return _type->isFloatTy();
}

bool IRType::isBoolType() {
    return _type->isIntegerTy(1);
}

bool IRType::isLiteralType() {
    return this->isIntegerType() || this->isFloatType() || this->isBoolType() || this->isCharType();
}

bool IRType::isArrayType() {
    return false;
}

bool IRType::isArrayPointerType() {
    return false;
}

bool IRType::isFunctionParameterType() {
    return false;
}

bool IRType::isLambdaType() {
    return false;
}

bool IRType::isStructType() {
    return false;
}

bool IRType::isEnumType() {
    return false;
}

bool IRType::isModuleType() {
    return false;
}

bool IRType::isPointerType() {
    return false;
}

bool IRType::isFunctionType() {
    return _type->isFunctionTy();
}

bool IRType::isClassType() {
    return false;
}

bool IRType::isTypeValueType() {
    return false;
}

bool IRType::isRefType() {
    return false;
}

bool IRType::containsTypeThatRequiresFreeing() {
    return false;
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

void IRType::print() {
    _type->print(llvm::outs(), true, true);
}