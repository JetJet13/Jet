//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_SYMBOL_TABLE_H
#define JETLANG_SYMBOL_TABLE_H

#include "../../shared/hash-table/hash-table.h"
#include "symbol.h"

class SymbolTable {
private:
    std::unordered_map<SymbolType, Symbol*, std::hash<int>> _table;
    void init();
    void insert(SymbolType symbolType, Symbol* symbol);
public:
    SymbolTable();
    Symbol* get(SymbolType symbolType);
};

#endif //JETLANG_SYMBOL_TABLE_H
