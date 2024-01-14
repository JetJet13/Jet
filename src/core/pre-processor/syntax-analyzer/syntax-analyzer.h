//
// Created by Johny Georges on 2024-01-10.
//

#ifndef JETLANG_SYNTAX_ANALYZER_H
#define JETLANG_SYNTAX_ANALYZER_H

#include "../../token/token-table.h"
#include "../../lexeme/lexeme.h"

class SyntaxAnalyzer {
private:
    TokenTable* _tokenTable;
public:
    explicit SyntaxAnalyzer(TokenTable* tokenTable);
    void analyze(Lexeme* lexeme);
};

#endif //JETLANG_SYNTAX_ANALYZER_H
