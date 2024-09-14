//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-pointer-type.h"
#include "../../shared/utils/logger/logger.h"

IRPointerType* IRPointerType::create(llvm::GlobalVariable* globalVariable) {
    return new IRPointerType(globalVariable->getType(), new IRType(globalVariable->getValueType()));
}

IRPointerType* IRPointerType::create(IRType* type) {
    return new IRPointerType(llvm::PointerType::get(type->getType(), 0), type);
}

IRPointerType::IRPointerType(llvm::PointerType* type, IRType* sourceType) : IRType(type) {
    _type = type;
    _sourceType = sourceType;
}

IRPointerType::IRPointerType(llvm::PointerType* type) : IRType(type) {
    _type = type;
    _sourceType = {};
}

llvm::PointerType* IRPointerType::getType() {
    return _type;
}

uint64_t IRPointerType::getSizeInBytes() {
    return 1;
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
    llvm::outs().write_escaped("IR POINTER TYPE ->");
    _type->print(llvm::outs(), true, true);
    llvm::outs().write(' ');
    if (_sourceType) {
        _sourceType.value()->print();
    } else {
        llvm::outs().write_escaped("NO SOURCE POINTER TYPE");
    }
    llvm::outs().write_escaped("<- IR POINTER TYPE");
}