//
// Created by Johny Georges on 2024-06-19.
//

#ifndef JETLANG_IR_TYPE_H
#define JETLANG_IR_TYPE_H

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

class IRType {
protected:
    llvm::Type* _type;
public:
    explicit IRType(llvm::Type* type);
    virtual llvm::Type* getType();
    virtual IRType* getSourceType();
    bool isCharType();
    bool isIntegerType();
    bool isFloatType();
    bool isBoolType();
    bool isArrayType();
    bool isStructType();
    virtual bool isPointerType();
    bool isFunctionType();
    bool isEqual(IRType* otherValue);
    bool isNotEqual(IRType* otherValue);
    bool isLessThan(IRType* otherValue);
    bool isLessThanOrEqual(IRType* otherValue);
    bool isGreaterThan(IRType* otherValue);
    bool isGreaterThanOrEqual(IRType* otherValue);
    virtual void print();
};

#endif //JETLANG_IR_TYPE_H
