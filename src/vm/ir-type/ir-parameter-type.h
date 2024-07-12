//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_IR_PARAMETER_TYPE_H
#define JETLANG_IR_PARAMETER_TYPE_H

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include "ir-type.h"

class IRParameterType {
private:
    std::string _name;
    IRType* _type;
public:
    IRParameterType(std::string name, IRType* type);
    std::string getName();
    IRType* getIRType();
    llvm::Type* getType();
};

#endif //JETLANG_IR_PARAMETER_TYPE_H
