//
// Created by Johny Georges on 2024-06-19.
//

#include <llvm/IR/Type.h>
#include "ir-type.h"
#include "../ir-nodes/ir-type-value-instruction-node.h"
#include "../../shared/utils/logger/logger.h"

IRType::IRType(llvm::Type* type) {
    _type = type;
    _alignmentOverride = {};
    _sizeInBytesOverride = {};
}

llvm::Type* IRType::getType() {
    return _type;
}

std::shared_ptr<IRType> IRType::getUnderlyingType() {
    return shared_from_this();
}

std::shared_ptr<IRType> IRType::getSourceType() {
    return shared_from_this();
}

uint64_t IRType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    } else if (this->isCharType() || this->isBoolType()) {
        return 1;
    } else if (this->isIntegerType() || this->isPointerType() || this->isFloatType() || this->isInteger64Type()) {
        return 8;
    } else {
        return 0;
    }
}

std::string IRType::getId() {
    return _id;
}

std::string IRType::getModuleId() {
    return _moduleId;
}

bool IRType::hasId() {
    return !_id.empty();
}

void IRType::setId(std::string id) {
    _id = id;
}

void IRType::setModuleId(std::string id) {
    _moduleId = id;
}

void IRType::setValue(std::shared_ptr<IRTypeValueInstructionNode> value) {
    _value = value;
}

void IRType::initClone(std::shared_ptr<IRType> irType) {
    irType->setId(_id);
    if (_alignmentOverride) {
        irType->setAlignmentOverride(_alignmentOverride.value());
    }

    if (_sizeInBytesOverride) {
        irType->setSizeInBytesOverride(_sizeInBytesOverride.value());
    }

    if (_value) {
        irType->setValue(_value.value()->clone());
    }
}

std::shared_ptr<IRType> IRType::clone() {
    auto clone = std::make_shared<IRType>(_type);
    this->initClone(clone);
    return clone;
}

std::shared_ptr<IRTypeValueInstructionNode> IRType::getValue() {
    if (!_value) {
        throw std::logic_error("ir type has no value");
    }
    return _value.value();
}

void IRType::setSizeInBytesOverride(unsigned long sizeInBytes) {
    _sizeInBytesOverride = sizeInBytes;
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

    if (this->isStructRefType() || this->isArrayPointerType() || this->isTypeValueType() || this->isRefType() || this->isPointerType()) {
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
    return _type->isDoubleTy();
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

bool IRType::isInvocableType() {
    return false;
}

bool IRType::isLambdaType() {
    return false;
}

bool IRType::isStructType() {
    return false;
}

bool IRType::isStructRefType() {
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

bool IRType::isClassInstanceType() {
    return false;
}

bool IRType::isNewClassInstanceType() {
    return false;
}

bool IRType::isTypeValueType() {
    return false;
}

bool IRType::isRefType() {
    return false;
}

bool IRType::isSharedType() {
    return false;
}

bool IRType::isVoidType() {
    return _type->isVoidTy();
}

bool IRType::isCapturedVariableType() {
    return false;
}

bool IRType::containsTypeThatRequiresFreeing() {
    return false;
}

bool IRType::requiresArc() {
    return false;
}

bool IRType::isEqual(std::shared_ptr<IRType> otherValue) {
    if (this->isIntegerType() && otherValue->isIntegerType()) {
        return this->getType()->getIntegerBitWidth() == otherValue->getType()->getIntegerBitWidth();
    }

    if (this->isFloatType() && otherValue->isFloatType()) {
        return this->getType()->getFPMantissaWidth() == otherValue->getType()->getFPMantissaWidth();
    }

    if (this->isArrayType() && otherValue->isArrayType()) {
        auto elementType = std::make_shared<IRType>(this->getType()->getArrayElementType());
        auto otherElementType = std::make_shared<IRType>(otherValue->getType()->getArrayElementType());
        return this->getType()->getArrayNumElements() == otherValue->getType()->getArrayNumElements() &&
                elementType->isEqual(otherElementType);
    }

    return false;
}

bool IRType::isNotEqual(std::shared_ptr<IRType> otherValue) {
    return !this->isEqual(otherValue);
}

bool IRType::isLessThan(std::shared_ptr<IRType> otherValue) {
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

bool IRType::isLessThanOrEqual(std::shared_ptr<IRType> otherValue) {
    return this->isEqual(otherValue) || this->isLessThan(otherValue);
}

bool IRType::isGreaterThan(std::shared_ptr<IRType> otherValue) {
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

bool IRType::isGreaterThanOrEqual(std::shared_ptr<IRType> otherValue) {
    return this->isEqual(otherValue) || this->isGreaterThan(otherValue);
}

void IRType::print() {
    _type->print(llvm::outs(), true, true);
}