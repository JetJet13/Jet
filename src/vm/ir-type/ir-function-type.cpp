//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-function-type.h"

IRFunctionType::IRFunctionType(llvm::FunctionType* type, bool requiresScopeArgument) : IRType(type) {
    _type = type;
    _requiresScopeArgument = requiresScopeArgument;
}

bool IRFunctionType::requiresScopeArgument() {
    return _requiresScopeArgument;
}

llvm::FunctionType* IRFunctionType::getType() {
    return _type;
}

std::shared_ptr<IRType> IRFunctionType::clone() {
    auto clone = std::make_shared<IRFunctionType>(_type);
    this->initClone(clone);
    return clone;
}