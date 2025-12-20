//
// Created by Johny Georges on 2025-12-18.
//

#ifndef JETLANG_IR_STRUCT_POINTER_TYPE_H
#define JETLANG_IR_STRUCT_POINTER_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"
#include "ir-struct-type.h"

class IRStructRefType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _structIndex;
    unsigned int _counterIndex;
    IRType* _counterIRType;
    IRStructType* _structIRType;
public:
    explicit IRStructRefType(llvm::StructType* type, IRType* counterIRType, IRStructType* structIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getStructIndex() const;
    [[nodiscard]] unsigned int getCounterIndex() const;
    llvm::PointerType* getStructType();
    llvm::PointerType* getCounterType();
    IRType* getCounterIRType();
    IRStructType* getStructIRType();
    bool isStructRefType() override;
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    IRStructRefType* clone() override;
};

#endif //JETLANG_IR_STRUCT_POINTER_TYPE_H
