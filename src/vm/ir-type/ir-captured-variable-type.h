//
// Created by Johny Georges on 2025-12-01.
//

#ifndef JETLANG_IR_CAPTURED_VARIABLE_TYPE_H
#define JETLANG_IR_CAPTURED_VARIABLE_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRCapturedVariableType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _variableIndex;
    unsigned int _captureCounterIndex;
    std::shared_ptr<IRType> _captureCounterIRType;
    std::shared_ptr<IRType> _variableIRType;
public:
    explicit IRCapturedVariableType(llvm::StructType* type, std::shared_ptr<IRType> captureCounterIRType, std::shared_ptr<IRType> variableIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getVariableIndex() const;
    [[nodiscard]] unsigned int getCaptureCounterIndex() const;
    llvm::PointerType* getVariableType();
    llvm::PointerType* getCaptureCounterType();
    std::shared_ptr<IRType> getCaptureCounterIRType();
    std::shared_ptr<IRType> getVariableIRType();
    std::shared_ptr<IRType> getUnderlyingType() override;
    uint64_t getSizeInBytes() override;
    bool isCapturedVariableType() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    std::shared_ptr<IRType> clone() override;
};

#endif //JETLANG_IR_CAPTURED_VARIABLE_TYPE_H
