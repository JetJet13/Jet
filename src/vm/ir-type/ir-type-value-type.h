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
// Created by Johny Georges on 2025-04-12.
//

#ifndef JETLANG_IR_TYPE_VALUE_TYPE_H
#define JETLANG_IR_TYPE_VALUE_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRTypeValueType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _idIndex;
    unsigned int _sizeInBytesIndex;
    unsigned int _numTypesIndex;
    unsigned int _allocIndex;
    unsigned int _keyIndex;
    unsigned int _valueIdIndex;
public:
    explicit IRTypeValueType(llvm::StructType* type);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getIdIndex() const;
    [[nodiscard]] unsigned int getSizeInBytesIndex() const;
    [[nodiscard]] unsigned int getNumTypesIndex() const;
    [[nodiscard]] unsigned int getAllocIndex() const;
    [[nodiscard]] unsigned int getKeyIndex() const;
    [[nodiscard]] unsigned int getValueIdIndex() const;
    llvm::PointerType* getAllocType();
    llvm::PointerType* getKeyType();
    llvm::PointerType* getValueIdType();
    uint64_t getSizeInBytes() override;
    std::shared_ptr<IRType> clone() override;
    bool isTypeValueType() override;
};

#endif //JETLANG_IR_TYPE_VALUE_TYPE_H
