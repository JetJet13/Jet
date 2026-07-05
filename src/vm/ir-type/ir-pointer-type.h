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
    std::optional<std::shared_ptr<IRType>> _sourceType;
public:
    static std::shared_ptr<IRPointerType> create(llvm::GlobalVariable* globalVariable);
    static std::shared_ptr<IRPointerType> create(std::shared_ptr<IRType> type);
    IRPointerType(llvm::PointerType* type, std::shared_ptr<IRType> sourceType);
    explicit IRPointerType(llvm::PointerType* type);
    llvm::PointerType* getType() override;
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    std::shared_ptr<IRType> getUnderlyingType() override;
    std::shared_ptr<IRType> getSourceType() override;
    void setSourceType(std::shared_ptr<IRType> type);
    bool containsTypeThatRequiresFreeing() override;
    bool isPointerType() override;
    std::shared_ptr<IRType> clone() override;
    virtual void print() override;
};

#endif //JETLANG_IR_POINTER_TYPE_H
