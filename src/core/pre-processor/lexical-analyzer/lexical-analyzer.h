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
    std::shared_ptr<ReservedKeywords> _reservedKeywords;
    CharTable _charTable;
    std::shared_ptr<TokenTable> _tokenTable;
    int _tokenValueIdCursor;
    bool _hasMore;
    std::optional<std::shared_ptr<Token>> _prevToken;
    std::optional<std::shared_ptr<Token>> buildNextToken();
    std::optional<std::shared_ptr<Token>> peekNextToken();
    void skipWhitespaceAndNewLine();
    void skipComments();
    void stopIfNecessary();
    int generateTokenValueId();
    void resetAfterPeek(Cursor cursor, int numAdvances);
public:
    LexicalAnalyzer(std::shared_ptr<TokenTable> tokenTable, std::shared_ptr<ReservedKeywords> reservedKeywords);
    void start(std::string &filePath);
    void stop();
    std::optional<std::shared_ptr<Lexeme>> next();
    std::optional<std::shared_ptr<Lexeme>> peek();
    bool hasMore();
};

#endif //JETLANG_LEXICAL_ANALYZER_H
