//
// Created by Johny Georges on 2023-12-29.
//

#include "reserved-keywords.h"
#include "../symbol/symbol-factory.h"

ReservedKeywords::ReservedKeywords() {
    _keywordMap = std::unordered_map<std::string, Symbol*>();
    this->init();
}

std::optional<Symbol*> ReservedKeywords::match(const std::string& matchTerm) {
    auto result = _keywordMap.find(matchTerm);
    if (result == _keywordMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<Symbol*> ReservedKeywords::match(char matchChar) {
    std::string matchTerm;
    matchTerm += matchChar;
    return this->match(matchTerm);
}

void ReservedKeywords::init() {
    this->add("int", SymbolFactory::createIntSymbol());
    this->add("=", SymbolFactory::createEqualSymbol());
    this->add("let", SymbolFactory::createVarSymbol());
    this->add("const", SymbolFactory::createConstSymbol());
    this->add(";", SymbolFactory::createSemicolonSymbol());
}

void ReservedKeywords::add(const std::string& keyword, Symbol* symbol) {
    _keywordMap.insert(std::pair<std::string, Symbol*>(keyword, symbol));
}
