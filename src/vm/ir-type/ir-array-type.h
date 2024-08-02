//
// Created by Johny Georges on 2024-08-02.
//

#ifndef JETLANG_IR_ARRAY_TYPE_H
#define JETLANG_IR_ARRAY_TYPE_H

#include "ir-struct-type.h"
#include "ir-pointer-type.h"

class IRArrayType : public IRType {
private:
    IRPointerType* _arrayElementType;
public:
    IRArrayType(IRPointerType* arrayElementType);
    llvm::ArrayType* getType() override;
    IRPointerType* getElementIRType();
};

#endif //JETLANG_IR_ARRAY_TYPE_H
