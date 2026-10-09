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

#include "binary-arithmetic-dsu.h"


BinaryArithmeticDSU::BinaryArithmeticDSU(llvm::Value* irValue) {
    _irValue = irValue;
    _children = std::vector<std::shared_ptr<BinaryArithmeticDSU>>();
}

llvm::Value* BinaryArithmeticDSU::getValue() {
    if (_parent) {
        return _parent.value()->getValue();
    }
    return _irValue;
}

void BinaryArithmeticDSU::merge(std::shared_ptr<BinaryArithmeticDSU> other) {
    other->setParent(shared_from_this());
    _children.push_back(other);
}

void BinaryArithmeticDSU::setParent(std::shared_ptr<BinaryArithmeticDSU> parent) {
    _parent = parent;
}
