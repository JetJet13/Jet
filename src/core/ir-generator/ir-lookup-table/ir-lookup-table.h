//
// Created by Johny Georges on 2024-06-12.
//

#ifndef JETLANG_IR_LOOKUP_TABLE_H
#define JETLANG_IR_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "llvm/IR/Value.h"

class IRLookupTable {
private:
    std::unordered_map<std::string, llvm::Value*> _scope;
    std::optional<IRLookupTable*> _outerScope;
public:
    explicit IRLookupTable(std::optional<IRLookupTable*> outerScope = {});
    IRLookupTable* insert(std::string key, llvm::Value* value);
    llvm::Value* find(std::string key);
    void dump();
};

#endif //JETLANG_IR_LOOKUP_TABLE_H
