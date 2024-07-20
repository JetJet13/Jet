//
// Created by Johny Georges on 2024-06-12.
//

#ifndef JETLANG_IR_LOOKUP_TABLE_H
#define JETLANG_IR_LOOKUP_TABLE_H

#include <unordered_map>
#include <optional>
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"

class IRLookupTable {
private:
    std::unordered_map<std::string, llvm::AllocaInst*> _scope;
    std::optional<IRLookupTable*> _outerScope;
public:
    explicit IRLookupTable(std::optional<IRLookupTable*> outerScope = {});
    IRLookupTable* insert(std::string key, llvm::AllocaInst* value);
    std::optional<llvm::AllocaInst*> find(std::string key);
    void dump();
};

#endif //JETLANG_IR_LOOKUP_TABLE_H
