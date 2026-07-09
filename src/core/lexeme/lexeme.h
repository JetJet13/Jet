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
    std::shared_ptr<Token> _token;
    std::shared_ptr<Position> _startPosition;
    std::shared_ptr<Position> _endPosition;
public:
    Lexeme(std::shared_ptr<Token> token);
    Lexeme(std::shared_ptr<Token> token, unsigned long startLine, unsigned long startColumn, unsigned long endLine, unsigned long endColumn);
    std::shared_ptr<Token> getToken();
    std::shared_ptr<Position> getStartPosition();
    std::shared_ptr<Position> getEndPosition();
    std::string toString();
    bool hasSameSymbolTypeAs(std::shared_ptr<Lexeme> other);
    bool isEqualTo(std::shared_ptr<Lexeme> other);
};

#endif //JETLANG_LEXEME_H
