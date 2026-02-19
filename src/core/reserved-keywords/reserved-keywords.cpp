//
// Created by Johny Georges on 2023-12-29.
//

#include "reserved-keywords.h"
#include "../symbol/symbol-factory.h"

ReservedKeywords::ReservedKeywords() {
    _keywordMap = std::unordered_map<std::string, std::shared_ptr<Symbol>>();
    _keywordSymbols = std::vector<std::shared_ptr<Symbol>>();
    this->init();
}

std::optional<std::shared_ptr<Symbol>> ReservedKeywords::match(const std::string& matchTerm) {
    auto result = _keywordMap.find(matchTerm);
    if (result == _keywordMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<std::shared_ptr<Symbol>> ReservedKeywords::match(std::optional<char> matchChar) {
    if (!matchChar) {
        return {};
    }
    std::string matchTerm;
    matchTerm += matchChar.value();
    return this->match(matchTerm);
}

bool ReservedKeywords::isKeywordSymbol(std::shared_ptr<Symbol> symbol) {
    return std::find(_keywordSymbols.begin(),
                     _keywordSymbols.end(),
                     symbol) != _keywordSymbols.end();
}

void ReservedKeywords::init() {
    this->add("int", SymbolFactory::createIntTypeSymbol());
    this->add("float", SymbolFactory::createFloatTypeSymbol());
    this->add("string", SymbolFactory::createStringTypeSymbol());
    this->add("char", SymbolFactory::createCharTypeSymbol());
    this->add("bool", SymbolFactory::createBooleanTypeSymbol());
    this->add("void", SymbolFactory::createVoidSymbol());
    this->add("=", SymbolFactory::createEqualSymbol());
    this->add("*=", SymbolFactory::createStarEqualSymbol());
    this->add("let", SymbolFactory::createLetSymbol());
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
    this->add("module", SymbolFactory::createModuleSymbol());
    this->add("as", SymbolFactory::createAsSymbol());
    this->add("import", SymbolFactory::createImportSymbol());
    this->add("use", SymbolFactory::createUseSymbol());
    this->add("from", SymbolFactory::createFromSymbol());
    this->add("..", SymbolFactory::createDotDotSymbol());
    this->add("...", SymbolFactory::createDotDotDotSymbol());
    this->add("::", SymbolFactory::createColonColonSymbol());
    this->add("class", SymbolFactory::createClassSymbol());
    this->add("public", SymbolFactory::createPublicSymbol());
    this->add("protected", SymbolFactory::createProtectedSymbol());
    this->add("private", SymbolFactory::createPrivateSymbol());
    this->add("static", SymbolFactory::createStaticSymbol());
    this->add("this", SymbolFactory::createThisSymbol());
    this->add("constructor", SymbolFactory::createConstructorSymbol());
    this->add("new", SymbolFactory::createNewSymbol());
    this->add("export", SymbolFactory::createExportSymbol());
    this->add("ref", SymbolFactory::createRefSymbol());
    this->add("dref", SymbolFactory::createDrefSymbol());
    this->add("sref", SymbolFactory::createSrefSymbol());
    this->add("++", SymbolFactory::createConcatSymbol());
    this->add("interface", SymbolFactory::createInterfaceSymbol());
    this->add("implements", SymbolFactory::createImplementsSymbol());
    this->add("type", SymbolFactory::createTypeSymbol());

    this->initKeywordSymbolList();
}

void ReservedKeywords::initKeywordSymbolList() {
    for (const auto& keyword : _keywordMap) {
        _keywordSymbols.push_back(keyword.second);
    }
}

void ReservedKeywords::add(const std::string& keyword, std::shared_ptr<Symbol> symbol) {
    _keywordMap.insert(std::pair<std::string, std::shared_ptr<Symbol>>(keyword, symbol));
}
