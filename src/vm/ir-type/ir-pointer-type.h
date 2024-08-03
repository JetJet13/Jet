//
// Created by Johny Georges on 2024-08-02.
//

#ifndef JETLANG_IR_POINTER_TYPE_H
#define JETLANG_IR_POINTER_TYPE_H

#include "ir-type.h"

class IRPointerType : public IRType {
private:
    llvm::PointerType* _type;
    IRType* _sourceType;
public:
    IRPointerType(llvm::PointerType* type, IRType* sourceType);
    IRType* getPointerSourceIRType();
    void setSourceType(IRType* type);
};

#endif //JETLANG_IR_POINTER_TYPE_H
