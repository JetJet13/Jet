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
    std::shared_ptr<IRType> _refCounterIRType;
    std::shared_ptr<IRType> _refIRType;
public:
    explicit IRRefType(llvm::StructType* type, std::shared_ptr<IRType> refCounterIRType, std::shared_ptr<IRType> refIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getRefValueIndex() const;
    [[nodiscard]] unsigned int getRefCounterIndex() const;
    llvm::PointerType* getRefValueType();
    llvm::PointerType* getRefCounterType();
    std::shared_ptr<IRType> getRefCounterIRType();
    std::shared_ptr<IRType> getRefValueIRType();
    std::shared_ptr<IRType> getUnderlyingType() override;
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    bool containsTypeThatRequiresFreeing() override;
    std::shared_ptr<IRType> clone() override;
    bool requiresArc() override;
    bool isRefType() override;
};

#endif //JETLANG_IR_REF_TYPE_H
