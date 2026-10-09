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
