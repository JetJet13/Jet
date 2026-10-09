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
    unsigned int _refCounterIndex;
    std::shared_ptr<IRType> _refCounterIRType;
    std::shared_ptr<IRType> _sharedIRType;
public:
    explicit IRSharedPtrType(llvm::StructType* type, std::shared_ptr<IRType> refCounterIRType, std::shared_ptr<IRType> sharedIRType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getSharedValueIndex() const;
    [[nodiscard]] unsigned int getRefCounterIndex() const;
    llvm::PointerType* getSharedValueType();
    llvm::PointerType* getRefCounterType();
    std::shared_ptr<IRType> getRefCounterIRType();
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
