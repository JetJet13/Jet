//
// Created by Johny Georges on 2024-06-19.
//

#ifndef JETLANG_IR_TYPE_H
#define JETLANG_IR_TYPE_H

#include <llvm/Support/Alignment.h>
#include <llvm/IR/DerivedTypes.h>

// forward declaration
class IRInstructionNode;

class IRType {
protected:
    llvm::Type* _type;
    std::optional<IRInstructionNode*> _value;
    std::optional<llvm::Align> _alignmentOverride;
    std::optional<unsigned long> _sizeInBytesOverride;
public:
    explicit IRType(llvm::Type* type);
    virtual llvm::Type* getType();
    virtual IRType* getSourceType();
    virtual uint64_t getSizeInBytes();
    virtual llvm::Align getAlignment();
    virtual void setAlignmentOverride(llvm::Align alignmentOverride);
    void setValue(IRInstructionNode* value);
    IRInstructionNode* getValue();
    void setSizeInBytesOverride(unsigned long sizeInBytes);
    bool hasValue();
    bool isCharType();
    bool isIntegerType();
    bool isInteger64Type();
    bool isFloatType();
    bool isBoolType();
    bool isLiteralType();
    virtual bool isArrayType();
    virtual bool isStructType();
    virtual bool isEnumType();
    virtual bool isModuleType();
    virtual bool isPointerType();
    virtual bool isArrayPointerType();
    virtual bool isFunctionParameterType();
    virtual bool isLambdaType();
    virtual bool isFunctionType();
    virtual bool isClassType();
    virtual bool isTypeValueType();
    virtual bool isRefType();
    virtual bool containsTypeThatRequiresFreeing();
    bool isEqual(IRType* otherValue);
    bool isNotEqual(IRType* otherValue);
    bool isLessThan(IRType* otherValue);
    bool isLessThanOrEqual(IRType* otherValue);
    bool isGreaterThan(IRType* otherValue);
    bool isGreaterThanOrEqual(IRType* otherValue);
    virtual void print();
};

#endif //JETLANG_IR_TYPE_H
