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
    int _line;
    int _start_position;
public:
    Lexeme(Token* token, int line, int startPosition);
    Token* getToken();
    int getLine() const;
    int getPosition() const;
    std::string toString();
    bool hasSameSymbolTypeAs(Lexeme* other);
    bool isEqualTo(Lexeme* other);
};

#endif //JETLANG_LEXEME_H
