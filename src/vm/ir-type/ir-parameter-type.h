//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_IR_PARAMETER_TYPE_H
#define JETLANG_IR_PARAMETER_TYPE_H

#include <llvm/IR/Type.h>
#include "ir-pointer-type.h"

class IRParameterType {
private:
    std::string _name;
    std::shared_ptr<IRType> _type;
public:
    IRParameterType(std::string name, std::shared_ptr<IRType> type);
    std::string getName();
    std::shared_ptr<IRType> getIRType();
    llvm::Type* getType();
    std::shared_ptr<IRParameterType> clone();
};

#endif //JETLANG_IR_PARAMETER_TYPE_H
