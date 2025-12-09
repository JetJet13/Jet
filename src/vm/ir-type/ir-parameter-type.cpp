//
// Created by Johny Georges on 2024-07-12.
//

#include "ir-parameter-type.h"

IRParameterType::IRParameterType(std::string name, IRType* type) {
    _name = name;
    _type = type;
}

std::string IRParameterType::getName() {
    return _name;
}

IRType* IRParameterType::getIRType() {
    return _type;
}

llvm::Type* IRParameterType::getType() {
    return _type->getType();
}

IRParameterType* IRParameterType::clone() {
    auto typeClone = _type->clone();
    return new IRParameterType(_name, typeClone);
}