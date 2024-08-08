//
// Created by Johny Georges on 2024-08-08.
//

#include "ir-array-type.h"

IRArrayType::IRArrayType(llvm::StructType* type) : IRType(type) {
    _type = type;
}