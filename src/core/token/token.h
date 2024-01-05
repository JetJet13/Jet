//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_TOKEN_H
#define JETLANG_TOKEN_H

#include <optional>
#include "../symbol/symbol.h"
#include "../../shared/types/null-type.h"

class Token {
private:
    Symbol* _symbol;
    std::optional<int> _valueId;
public:
    explicit Token(Symbol* symbol);
    void setValueId(int valueId);
    std::optional<int> getValueId();
    std::string toString();
};

#endif //JETLANG_TOKEN_H
