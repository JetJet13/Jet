//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_IR_REF_TYPE_H
#define JETLANG_IR_REF_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRRefType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _refValueIndex;
    unsigned int _refCounterIndex;
    IRType* _refCounterIRType;
    IRType* _refIRType;
public:
    explicit IRRefType(llvm::StructType* type, IRType* refCounterIRType, IRType* refIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getRefValueIndex() const;
    [[nodiscard]] unsigned int getRefCounterIndex() const;
    llvm::PointerType* getRefValueType();
    llvm::PointerType* getRefCounterType();
    IRType* getRefCounterIRType();
    IRType* getRefValueIRType();
    uint64_t getSizeInBytes() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isRefType() override;
};

#endif //JETLANG_IR_REF_TYPE_H
