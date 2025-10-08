//
// Created by Johny Georges on 2024-12-31.
//

#include "ir-class-instance-type.h"
#include "../../shared/utils/logger/logger.h"

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

std::string IRClassInstanceType::getIRMethodName(std::string methodName) {
    return _irClassType->getName() + "_" + methodName;
}

std::optional<IRFunctionType*> IRClassInstanceType::getIRTypeForMethod(std::string methodName) {
    return _irClassType->getIRTypeForMethod(this->getIRMethodName(methodName));
}

llvm::StructType* IRClassInstanceType::getType() {
    return _irClassType->getClassProperties()->getType();
}

bool IRClassInstanceType::containsTypeThatRequiresFreeing() {
    return _irClassType->containsTypeThatRequiresFreeing();
}

bool IRClassInstanceType::isClassInstanceType() {
    return true;
}

llvm::Align IRClassInstanceType::getAlignment() {
    return _irClassType->getAlignment();
}

void IRClassInstanceType::print() {
    Logger::log("IR CLASS INSTANCE TYPE");
    _type->print(llvm::outs());
}