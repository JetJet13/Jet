//
// Created by Johny Georges on 2024-01-17.
//

#ifndef JETLANG_FOLLOW_SYMBOL_TABLE_H
#define JETLANG_FOLLOW_SYMBOL_TABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../../symbol/types/symbol-type.h"

class FollowSymbolTable {
private:
    std::unordered_map<SymbolType, std::vector<SymbolType>*, std::hash<int>> _followSymbolMap;
    void init();
    void add(SymbolType symbol, std::vector<SymbolType>* followSymbols);
public:
    FollowSymbolTable();
    bool isValidFollowSymbol(SymbolType followSymbolType, SymbolType symbolType);
};

#endif //JETLANG_FOLLOW_SYMBOL_TABLE_H
