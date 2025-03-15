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
