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

IRFunctionType* IRFunctionType::clone() {
    auto clone = new IRFunctionType(_type);
    this->initClone(clone);
    return clone;
}