//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_IR_PARAMETER_TYPE_H
#define JETLANG_IR_PARAMETER_TYPE_H

#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>
#include "ir-pointer-type.h"

class IRParameterType {
private:
    std::string _name;
    IRPointerType* _type;
public:
    IRParameterType(std::string name, IRPointerType* type);
    std::string getName();
    IRPointerType* getIRType();
    llvm::Type* getType();
};

#endif //JETLANG_IR_PARAMETER_TYPE_H
