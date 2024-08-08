//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-pointer-type.h"
#include "../../shared/utils/logger/logger.h"

IRPointerType* IRPointerType::create(llvm::GlobalVariable* globalVariable) {
    return new IRPointerType(globalVariable->getType(), new IRType(globalVariable->getValueType()));
}

IRPointerType::IRPointerType(llvm::PointerType* type, IRType* sourceType) : IRType(type) {
    _type = type;
    _sourceType = sourceType;
}

IRPointerType::IRPointerType(llvm::PointerType* type) : IRType(type) {
    _type = type;
    _sourceType = {};
}

IRType* IRPointerType::getSourceType() {
    if (!_sourceType) {
        throw std::logic_error("ir pointer does not have source ir type set");
    }
    return _sourceType.value();
}

void IRPointerType::setSourceType(IRType* type) {
    _sourceType = type;
}

bool IRPointerType::isPointerType() {
    return true;
}

void IRPointerType::print() {
    _type->print(llvm::outs(), true, true);
    llvm::outs().write(' ');
    if (_sourceType) {
        _sourceType.value()->print();
    } else {
        llvm::outs().write_escaped("NO SOURCE POINTER TYPE");
    }
}