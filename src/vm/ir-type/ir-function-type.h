//
// Created by Johny Georges on 2024-08-02.
//

#ifndef JETLANG_IR_FUNCTION_TYPE_H
#define JETLANG_IR_FUNCTION_TYPE_H

#include "ir-struct-type.h"

class IRFunctionType : public IRType {
private:
    llvm::FunctionType* _type;
public:
    IRFunctionType(llvm::FunctionType* type);
    llvm::FunctionType* getType() override;
};

#endif //JETLANG_IR_FUNCTION_TYPE_H
