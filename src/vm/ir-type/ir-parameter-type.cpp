//
// Created by Johny Georges on 2024-07-12.
//

#include "ir-parameter-type.h"

IRParameterType::IRParameterType(std::string name, IRPointerType* type) {
    _name = name;
    _type = type;
}

std::string IRParameterType::getName() {
    return _name;
}

IRPointerType* IRParameterType::getIRType() {
    return _type;
}

llvm::Type* IRParameterType::getType() {
    return _type->getType();
}