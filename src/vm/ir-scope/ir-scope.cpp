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

#include "ir-scope.h"

IRScope::IRScope(std::optional<IRScope*> parentScope) {
    _refObjects = std::unordered_map<int, llvm::Value*>();
    _parentScope = parentScope;
}

IRScope* IRScope::insert(int refId, llvm::Value* value) {
    _refObjects[refId] = value;
    return this;
}

bool IRScope::hasRefObject(int refId) {
    auto result = _refObjects.find(refId);
    return result != _refObjects.end();
}

std::vector<llvm::Value*> IRScope::getRefObjectsToDeAllocate() {
    auto refObjectsToDeAllocate = std::vector<llvm::Value*>();
    for (auto keyValue: _refObjects) {
        if (!_parentScope || !_parentScope.value()->hasRefObject(keyValue.first)) {
            refObjectsToDeAllocate.push_back(keyValue.second);
        }
    }
    return refObjectsToDeAllocate;
}