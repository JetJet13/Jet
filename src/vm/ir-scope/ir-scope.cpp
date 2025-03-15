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