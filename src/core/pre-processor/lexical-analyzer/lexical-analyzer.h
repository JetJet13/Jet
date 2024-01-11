//
// Created by Johny Georges on 2023-12-31.
//

#ifndef JETLANG_LEXICAL_ANALYZER_H
#define JETLANG_LEXICAL_ANALYZER_H


#include "../../file-reader/file-reader.h"
#include "../../lexeme/lexeme.h"
#include "../../reserved-keywords/reserved-keywords.h"
#include "../../token/token-table.h"
#include "../../char-table/char-table.h"

class LexicalAnalyzer {
private:
    FileReader _fileReader;
    ReservedKeywords _reservedKeywords;
    CharTable _charTable;
    TokenTable* _tokenTable;
    int _tokenValueIdCursor;
    bool _hasMore;
    std::optional<Token*> buildNextToken();
    void skipWhitespaceAndNewLine();
    void stopIfNecessary();
    int generateTokenValueId();
public:
    LexicalAnalyzer(TokenTable* tokenTable);
    void start(std::string &filePath);
    void stop();
    std::optional<Lexeme> next();
};

#endif //JETLANG_LEXICAL_ANALYZER_H
