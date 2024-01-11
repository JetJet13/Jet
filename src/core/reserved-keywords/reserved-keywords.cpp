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

std::optional<Symbol*> ReservedKeywords::match(std::optional<char> matchChar) {
    if (!matchChar) {
        return {};
    }
    std::string matchTerm;
    matchTerm += matchChar.value();
    return this->match(matchTerm);
}

void ReservedKeywords::init() {
    this->add("int", SymbolFactory::createIntSymbol());
    this->add("=", SymbolFactory::createEqualSymbol());
    this->add("let", SymbolFactory::createVarSymbol());
    this->add("const", SymbolFactory::createConstSymbol());
    this->add(";", SymbolFactory::createSemicolonSymbol());
    this->add("mod", SymbolFactory::createModuloSymbol());
    this->add("+", SymbolFactory::createPlusSymbol());
    this->add("-", SymbolFactory::createMinusSymbol());
    this->add("*", SymbolFactory::createStarSymbol());
    this->add("/", SymbolFactory::createSlashSymbol());
    this->add("<", SymbolFactory::createLessThenSymbol());
    this->add(">", SymbolFactory::createGreaterThenSymbol());
    this->add("true", SymbolFactory::createTrueSymbol());
    this->add("false", SymbolFactory::createFalseSymbol());
    this->add("&&", SymbolFactory::createAndSymbol());
    this->add("||", SymbolFactory::createOrSymbol());
    this->add("(", SymbolFactory::createLeftParenSymbol());
    this->add(")", SymbolFactory::createRightParenSymbol());
    this->add("{", SymbolFactory::createLeftBraceSymbol());
    this->add("}", SymbolFactory::createRightBraceSymbol());
    this->add("[", SymbolFactory::createLeftBracketSymbol());
    this->add("]", SymbolFactory::createRightBracketSymbol());
    this->add(":", SymbolFactory::createColonSymbol());
    this->add(",", SymbolFactory::createCommaSymbol());
    this->add(".", SymbolFactory::createPeriodSymbol());
    this->add("!", SymbolFactory::createBangSymbol());
    this->add("!=", SymbolFactory::createBangEqualSymbol());
    this->add("==", SymbolFactory::createEqualEqualSymbol());
}

void ReservedKeywords::add(const std::string& keyword, Symbol* symbol) {
    _keywordMap.insert(std::pair<std::string, Symbol*>(keyword, symbol));
}
