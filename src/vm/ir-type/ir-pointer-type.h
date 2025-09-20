//
// Created by Johny Georges on 2024-08-02.
//

#ifndef JETLANG_IR_POINTER_TYPE_H
#define JETLANG_IR_POINTER_TYPE_H

#include <llvm/IR/Instructions.h>
#include <llvm/IR/GlobalVariable.h>
#include "ir-type.h"

class IRPointerType : public IRType {
private:
    llvm::PointerType* _type;
    std::optional<IRType*> _sourceType;
public:
    static IRPointerType* create(llvm::GlobalVariable* globalVariable);
    static IRPointerType* create(IRType* type);
    IRPointerType(llvm::PointerType* type, IRType* sourceType);
    explicit IRPointerType(llvm::PointerType* type);
    llvm::PointerType* getType() override;
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    IRType* getSourceType() override;
    void setSourceType(IRType* type);
    bool containsTypeThatRequiresFreeing() override;
    bool isPointerType() override;
    virtual void print() override;
};

#endif //JETLANG_IR_POINTER_TYPE_H
