//
// Created by Johny Georges on 2024-08-08.
//

#ifndef JETLANG_IR_ARRAY_TYPE_H
#define JETLANG_IR_ARRAY_TYPE_H

#include "ir-type.h"

class IRArrayType : public IRType {
private:
    llvm::StructType* _type;
public:
    IRArrayType(llvm::StructType* type);
    void setPointerType(llvm::PointerType* pointerType);

};

#endif //JETLANG_IR_ARRAY_TYPE_H
