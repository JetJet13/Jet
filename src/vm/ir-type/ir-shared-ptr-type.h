//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_IR_SHARED_PTR_TYPE_H
#define JETLANG_IR_SHARED_PTR_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRSharedPtrType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _sharedValueIndex;
    unsigned int _sharedCounterIndex;
    std::shared_ptr<IRType> _sharedCounterIRType;
    std::shared_ptr<IRType> _sharedIRType;
public:
    explicit IRSharedPtrType(llvm::StructType* type, std::shared_ptr<IRType> sharedCounterIRType, std::shared_ptr<IRType> sharedIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getSharedValueIndex() const;
    [[nodiscard]] unsigned int getSharedCounterIndex() const;
    llvm::PointerType* getSharedValueType();
    llvm::PointerType* getSharedCounterType();
    std::shared_ptr<IRType> getSharedCounterIRType();
    std::shared_ptr<IRType> getSharedValueIRType();
    std::shared_ptr<IRType> getUnderlyingType() override;
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    bool containsTypeThatRequiresFreeing() override;
    std::shared_ptr<IRType> clone() override;
    bool requiresArc() override;
    bool isSharedType() override;
};

#endif //JETLANG_IR_SHARED_PTR_TYPE_H
