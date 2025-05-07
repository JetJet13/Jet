//
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_IR_CLASS_INSTANCE_TYPE_H
#define JETLANG_IR_CLASS_INSTANCE_TYPE_H

#include "ir-type.h"
#include "ir-class-type.h"

class IRClassInstanceType : public IRType {
private:
    IRClassType* _irClassType;
    IRFunctionType* _irConstructorType;
public:
    IRClassInstanceType(IRClassType* irClassType, IRFunctionType* irConstructorType);
    IRClassType* getIRClassType();
    IRFunctionType* getIRConstructorType();
    llvm::StructType* getType() override;
    bool containsTypeThatRequiresFreeing() override;
};

#endif //JETLANG_IR_CLASS_INSTANCE_TYPE_H
