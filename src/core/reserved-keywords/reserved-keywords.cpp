//
// Created by Johny Georges on 2023-12-29.
//

#include "reserved-keywords.h"
#include "../symbol/symbol-factory.h"

ReservedKeywords::ReservedKeywords() {
    _keywordMap = std::unordered_map<std::string, Symbol*>();
    _keywordSymbols = std::vector<Symbol*>();
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

bool ReservedKeywords::isKeywordSymbol(Symbol* symbol) {
    return std::find(_keywordSymbols.begin(),
                     _keywordSymbols.end(),
                     symbol) != _keywordSymbols.end();
}

void ReservedKeywords::init() {
    this->add("int", SymbolFactory::createIntTypeSymbol());
    this->add("float", SymbolFactory::createFloatTypeSymbol());
    this->add("string", SymbolFactory::createStringTypeSymbol());
    this->add("char", SymbolFactory::createCharTypeSymbol());
    this->add("boolean", SymbolFactory::createBooleanTypeSymbol());
    this->add("array", SymbolFactory::createArrayTypeSymbol());
    this->add("void", SymbolFactory::createVoidTypeSymbol());
    this->add("=", SymbolFactory::createEqualSymbol());
    this->add("let", SymbolFactory::createVarSymbol());
    this->add("const", SymbolFactory::createConstSymbol());
    this->add(";", SymbolFactory::createSemicolonSymbol());
    this->add("mod", SymbolFactory::createModuloSymbol());
    this->add("+", SymbolFactory::createPlusSymbol());
    this->add("-", SymbolFactory::createMinusSymbol());
    this->add("*", SymbolFactory::createStarSymbol());
    this->add("/", SymbolFactory::createSlashSymbol());
    this->add("<", SymbolFactory::createLessThanSymbol());
    this->add("<=", SymbolFactory::createLessThanOrEqualSymbol());
    this->add(">", SymbolFactory::createGreaterThanSymbol());
    this->add(">=", SymbolFactory::createGreaterThanOrEqualSymbol());
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
    this->add("func", SymbolFactory::createFunctionSymbol());
    this->add("return", SymbolFactory::createReturnSymbol());
    this->add("proc", SymbolFactory::createProcedureSymbol());
    this->add("enum", SymbolFactory::createEnumSymbol());
    this->add("tuple", SymbolFactory::createTupleSymbol());
    this->add("if", SymbolFactory::createIfSymbol());
    this->add("else", SymbolFactory::createElseSymbol());
    this->add("for", SymbolFactory::createForSymbol());
    this->add("in", SymbolFactory::createInSymbol());
    this->add("while", SymbolFactory::createWhileSymbol());
    this->add("break", SymbolFactory::createBreakSymbol());
    this->add("skip", SymbolFactory::createSkipSymbol());
    this->add("try", SymbolFactory::createTrySymbol());
    this->add("catch", SymbolFactory::createCatchSymbol());
    this->add("finally", SymbolFactory::createFinallySymbol());
    this->add("=>", SymbolFactory::createFatArrowSymbol());

    this->initKeywordSymbolList();
}

void ReservedKeywords::initKeywordSymbolList() {
    for (const auto& keyword : _keywordMap) {
        _keywordSymbols.push_back(keyword.second);
    }
}

void ReservedKeywords::add(const std::string& keyword, Symbol* symbol) {
    _keywordMap.insert(std::pair<std::string, Symbol*>(keyword, symbol));
}
