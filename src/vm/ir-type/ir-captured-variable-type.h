// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
