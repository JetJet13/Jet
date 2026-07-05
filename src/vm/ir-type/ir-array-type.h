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
    std::shared_ptr<IRType> _arrayElementType;
public:
    explicit IRArrayType(llvm::ArrayType* type, std::shared_ptr<IRType> arrayElementType);
    llvm::ArrayType* getType() override;
    std::shared_ptr<IRType> getElementIRType();
    llvm::Type* getElementType();
    uint64_t getSize();
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    llvm::Align getAlignment() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isArrayType() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_ARRAY_TYPE_H
