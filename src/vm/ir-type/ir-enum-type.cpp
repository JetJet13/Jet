//
// Created by Johny Georges on 2024-08-01.
//

#include "ir-enum-type.h"

llvm::Type* IREnumType::getValueType() {
    return this->getType()->getStructElementType(0);
}