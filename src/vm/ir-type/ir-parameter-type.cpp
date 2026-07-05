//
// Created by Johny Georges on 2024-07-12.
//

#include "ir-parameter-type.h"

IRParameterType::IRParameterType(std::string name, std::shared_ptr<IRType> type) {
    _name = name;
    _type = type;
}

std::string IRParameterType::getName() {
    return _name;
}

std::shared_ptr<IRType> IRParameterType::getIRType() {
    return _type;
}

llvm::Type* IRParameterType::getType() {
    return _type->getType();
}

std::shared_ptr<IRParameterType> IRParameterType::clone() {
    auto typeClone = _type->clone();
    return std::make_shared<IRParameterType>(_name, typeClone);
}