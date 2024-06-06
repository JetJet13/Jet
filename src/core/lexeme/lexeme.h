//
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LEXEME_H
#define JETLANG_LEXEME_H

#include <string>
#include "../symbol/symbol.h"
#include "../token/token.h"
#include "types/position.h"

class Lexeme {
private:
    Token* _token;
    Position _startPosition;
    Position _endPosition;
public:
    Lexeme(Token* token, unsigned long startLine, unsigned long startColumn, unsigned long endLine, unsigned long endColumn);
    Token* getToken();
    Position* getStartPosition();
    Position* getEndPosition();
    std::string toString();
    bool hasSameSymbolTypeAs(Lexeme* other);
    bool isEqualTo(Lexeme* other);
};

#endif //JETLANG_LEXEME_H
