//
// Created by Johny Georges on 2024-12-31.
//

#include "ir-class-instance-type.h"

IRClassInstanceType::IRClassInstanceType(IRClassType* irClassType, IRFunctionType* irConstructorType) : IRType(irClassType->getClassProperties()->getType()) {
    _irClassType = irClassType;
    _irConstructorType = irConstructorType;
}

IRClassType* IRClassInstanceType::getIRClassType() {
    return _irClassType;
}

IRFunctionType* IRClassInstanceType::getIRConstructorType() {
    return _irConstructorType;
}

llvm::StructType* IRClassInstanceType::getType() {
    return _irClassType->getClassProperties()->getType();
}

bool IRClassInstanceType::containsTypeThatRequiresFreeing() {
    return _irClassType->containsTypeThatRequiresFreeing();
}