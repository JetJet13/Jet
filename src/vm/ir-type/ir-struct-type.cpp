//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-struct-type.h"

IRStructType::IRStructType(llvm::StructType* type) : IRType(type) {
    _type = type;
}

llvm::StructType* IRStructType::getType() {
    return _type;
}