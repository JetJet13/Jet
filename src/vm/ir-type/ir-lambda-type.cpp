//
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-type.h"

IRLambdaType::IRLambdaType(llvm::FunctionType* type) : IRType(type) {
    _type = type;
}

llvm::FunctionType* IRLambdaType::getType() {
    return _type;
}