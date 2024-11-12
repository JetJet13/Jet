//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_IR_LAMBDA_TYPE_H
#define JETLANG_IR_LAMBDA_TYPE_H

#include "ir-struct-type.h"

class IRLambdaType : public IRType {
private:
    llvm::FunctionType* _type;
public:
    IRLambdaType(llvm::FunctionType* type);
    llvm::FunctionType* getType() override;
};

#endif //JETLANG_IR_LAMBDA_TYPE_H
