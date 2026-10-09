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
// Created by Johny Georges on 2024-08-08.
//

#ifndef JETLANG_IR_ARRAY_POINTER_TYPE_H
#define JETLANG_IR_ARRAY_POINTER_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRArrayPointerType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _numElementsIndex;
    unsigned int _depthIndex;
    unsigned int _allocIndex;
    std::shared_ptr<IRType> _arrayElementType;
public:
    explicit IRArrayPointerType(llvm::StructType* type, std::shared_ptr<IRType> arrayElementType);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getNumElementsIndex() const;
    [[nodiscard]] unsigned int getDepthIndex() const;
    [[nodiscard]] unsigned int getAllocIndex() const;
    llvm::Type* getNumElementsType();
    llvm::PointerType* getAllocType();
    std::shared_ptr<IRType> getElementIRType();
    llvm::Type* getElementType();
    uint64_t getDepth();
    uint64_t getSizeInBytes() override;
    void setAlignmentOverride(llvm::Align alignmentOverride) override;
    bool containsTypeThatRequiresFreeing() override;
    bool isArrayPointerType() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_ARRAY_POINTER_TYPE_H
