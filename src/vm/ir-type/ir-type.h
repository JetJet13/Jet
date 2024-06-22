//
// Created by Johny Georges on 2024-06-19.
//

#ifndef JETLANG_IR_TYPE_H
#define JETLANG_IR_TYPE_H

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

class IRType {
private:
    llvm::Type* _type;
public:
    IRType(llvm::Type* type);
    llvm::Type* getType();
    bool isCharType();
    bool isIntegerType();
    bool isFloatType();
    bool isBoolType();
    bool isArrayType();
    bool isStructType();
    bool isEqual(IRType* otherValue);
    bool isNotEqual(IRType* otherValue);
    bool isLessThan(IRType* otherValue);
    bool isLessThanOrEqual(IRType* otherValue);
    bool isGreaterThan(IRType* otherValue);
    bool isGreaterThanOrEqual(IRType* otherValue);
};

#endif //JETLANG_IR_TYPE_H
