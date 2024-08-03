//
// Created by Johny Georges on 2024-08-02.
//

#include "ir-function-type.h"

IRFunctionType::IRFunctionType(llvm::FunctionType* type) : IRType(type) {
    _type = type;
}

llvm::FunctionType* IRFunctionType::getType() {
    return _type;
}