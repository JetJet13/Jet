//
// Created by Johny Georges on 2023-12-29.
//

#ifndef JETLANG_RESERVED_KEYWORDS_H
#define JETLANG_RESERVED_KEYWORDS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../symbol/symbol.h"

class ReservedKeywords {
private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> _keywordMap;
    std::vector<std::shared_ptr<Symbol>> _keywordSymbols;
    void init();
    void initKeywordSymbolList();
    void add(const std::string& keyword, std::shared_ptr<Symbol> symbol);
public:
    ReservedKeywords();
    std::optional<std::shared_ptr<Symbol>> match(const std::string& matchTerm);
    std::optional<std::shared_ptr<Symbol>> match(std::optional<char> matchChar);
    bool isKeywordSymbol(std::shared_ptr<Symbol> symbol);
};
#endif //JETLANG_RESERVED_KEYWORDS_H
