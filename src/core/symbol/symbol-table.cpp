//
// Created by Johny Georges on 2023-12-27.
//

#include "symbol-table.h"
#include "symbol-factory.h"

SymbolTable::SymbolTable() {
    _table = std::unordered_map<SymbolType, Symbol*, std::hash<int>>();
    this->init();
}

void SymbolTable::init() {
    this->insert(SYM_CONST, SymbolFactory::createConstSymbol());
    this->insert(SYM_EQUAL, SymbolFactory::createEqualSymbol());
    this->insert(SYM_IDENTIFIER, SymbolFactory::createIdentifierSymbol());
    this->insert(SYM_INT, SymbolFactory::createIntSymbol());
    this->insert(SYM_SEMICOLON, SymbolFactory::createSemicolonSymbol());
    this->insert(SYM_VAR, SymbolFactory::createVarSymbol());
}

Symbol* SymbolTable::get(SymbolType symbolType) {
    auto result = _table.find(symbolType);
    if (result == _table.end()) {
        Logger::log("no symbol found for symbolType", ToStringUtil::toString(symbolType));
        throw std::runtime_error("no symbol found for symbolType");
    } else {
        return result->second;
    }

}

void SymbolTable::insert(SymbolType symbolType, Symbol* symbol) {
    _table.insert(std::pair<SymbolType, Symbol*>(symbolType, symbol));
}

