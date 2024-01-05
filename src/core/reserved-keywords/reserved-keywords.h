//
// Created by Johny Georges on 2023-12-29.
//

#ifndef JETLANG_RESERVED_KEYWORDS_H
#define JETLANG_RESERVED_KEYWORDS_H

#include <string>
#include <unordered_map>
#include "../symbol/symbol.h"

class ReservedKeywords {
private:
    std::unordered_map<std::string, Symbol*> _keywordMap;
    void init();
    void add(const std::string& keyword, Symbol* symbol);
public:
    ReservedKeywords();
    std::optional<Symbol*> match(const std::string& matchTerm);
    std::optional<Symbol*> match(char matchChar);

};
#endif //JETLANG_RESERVED_KEYWORDS_H
