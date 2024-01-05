//
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LEXEME_H
#define JETLANG_LEXEME_H

#include <string>
#include "../symbol/symbol.h"
#include "../token/token.h"

class Lexeme {
private:
    Token* _token;
    uint8_t _line;
    uint8_t _start_position;
public:
    Lexeme(Token* token, uint8_t line, uint8_t startPosition);
    Token* getToken();
    uint8_t getLine() const;
    uint8_t getPosition() const;
    std::string toString();
};

#endif //JETLANG_LEXEME_H
