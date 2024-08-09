//
// Created by Johny Georges on 2024-08-09.
//

#ifndef JETLANG_IR_ARRAY_TYPE_H
#define JETLANG_IR_ARRAY_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRArrayType : public IRType {
private:
    llvm::ArrayType* _type;
    IRType* _arrayElementType;
public:
    explicit IRArrayType(llvm::ArrayType* type, IRType* arrayElementType);
    llvm::ArrayType* getType() override;
    IRType* getElementIRType();
    llvm::Type* getElementType();
    uint64_t getSizeInBytes() override;
    bool isArrayType() override;
};

#endif //JETLANG_IR_ARRAY_TYPE_H
