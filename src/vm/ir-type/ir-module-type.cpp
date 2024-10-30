//
// Created by Johny Georges on 2024-10-29.
//

#include "ir-module-type.h"

llvm::Type* IRModuleType::getValueType() {
    return this->getType()->getStructElementType(0);
}

bool IRModuleType::isModuleType() {
    return true;
}