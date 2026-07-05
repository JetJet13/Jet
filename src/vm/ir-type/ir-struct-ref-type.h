//
// Created by Johny Georges on 2025-12-18.
//

#ifndef JETLANG_IR_STRUCT_REF_TYPE_H
#define JETLANG_IR_STRUCT_REF_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"
#include "ir-struct-type.h"

class IRStructRefType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _structIndex;
    unsigned int _counterIndex;
    std::shared_ptr<IRType> _counterIRType;
    std::shared_ptr<IRStructType> _structIRType;
public:
    explicit IRStructRefType(llvm::StructType* type, std::shared_ptr<IRType> counterIRType, std::shared_ptr<IRStructType> structIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getStructIndex() const;
    [[nodiscard]] unsigned int getCounterIndex() const;
    llvm::PointerType* getStructType();
    llvm::PointerType* getCounterType();
    std::shared_ptr<IRType> getCounterIRType();
    std::shared_ptr<IRStructType> getStructIRType();
    bool requiresArc() override;
    bool isStructRefType() override;
    uint64_t getSizeInBytes() override;
    bool containsTypeThatRequiresFreeing() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    std::shared_ptr<IRType> clone() override;
};

#endif //JETLANG_IR_STRUCT_REF_TYPE_H
