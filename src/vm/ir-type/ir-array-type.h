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
