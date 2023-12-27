//
// Created by Johny Georges on 2023-12-24.
//

#ifndef JETLANG_SYMBOL_H
#define JETLANG_SYMBOL_H

#include <string>

class Symbol {
protected:
    std::string _value;
public:
    virtual std::string toString() = 0;
};

#endif //JETLANG_SYMBOL_H
