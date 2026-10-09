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
// Created by Johny Georges on 2025-03-15.
//

#ifndef JETLANG_IR_SCOPE_H
#define JETLANG_IR_SCOPE_H

#include "llvm/IR/Value.h"
#include <unordered_map>
#include <optional>
#include <vector>

class IRScope {
private:
    std::unordered_map<int, llvm::Value*> _refObjects;
    std::optional<IRScope*> _parentScope;
public:
    IRScope(std::optional<IRScope*> parentScope = {});
    IRScope* insert(int refId, llvm::Value* value);
    bool hasRefObject(int refId);
    std::vector<llvm::Value*> getRefObjectsToDeAllocate();
};

#endif //JETLANG_IR_SCOPE_H
