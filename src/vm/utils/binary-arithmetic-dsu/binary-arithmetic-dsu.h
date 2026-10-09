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
// Created by Johny Georges on 2026-02-14.
//

#ifndef JETLANG_BINARY_ARITHMETIC_DSU_H
#define JETLANG_BINARY_ARITHMETIC_DSU_H

#include <llvm/IR/Value.h>
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"

// Binary Arithmetic Disjoint-Set-Union
class BinaryArithmeticDSU : public std::enable_shared_from_this<BinaryArithmeticDSU> {
private:
    llvm::Value* _irValue;
    std::optional<std::shared_ptr<BinaryArithmeticDSU>> _parent;
    std::vector<std::shared_ptr<BinaryArithmeticDSU>> _children;
public:
    BinaryArithmeticDSU(llvm::Value* irValue);
    llvm::Value* getValue();
    void merge(std::shared_ptr<BinaryArithmeticDSU> other);
    void setParent(std::shared_ptr<BinaryArithmeticDSU> parent);
};

#endif //JETLANG_BINARY_ARITHMETIC_DSU_H
