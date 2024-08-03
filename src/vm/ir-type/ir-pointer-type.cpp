//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-pointer-type.h"
#include "../../shared/utils/logger/logger.h"

IRPointerType* IRPointerType::create(llvm::AllocaInst* allocation) {
    return new IRPointerType(allocation->getType(), new IRType(allocation->getAllocatedType()));
}

IRPointerType* IRPointerType::create(llvm::GlobalVariable* globalVariable) {
    return new IRPointerType(globalVariable->getType(), new IRType(globalVariable->getValueType()));
}

IRPointerType::IRPointerType(llvm::PointerType* type, IRType* sourceType) : IRType(type) {
    _type = type;
    _sourceType = sourceType;
}

IRType* IRPointerType::getPointerSourceIRType() {
    if (_sourceType->isPointerType()) {
        return ((IRPointerType*)_sourceType)->getPointerSourceIRType();
    }
    return _sourceType;
}

void IRPointerType::setSourceType(IRType* type) {
    _sourceType = type;
}

bool IRPointerType::isPointerType() {
    return true;
}