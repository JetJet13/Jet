//
// Created by Johny Georges on 2023-12-31.
//

#ifndef JETLANG_LEXICAL_ANALYZER_H
#define JETLANG_LEXICAL_ANALYZER_H


#include "../../file-reader/file-reader.h"
#include "../../lexeme/lexeme.h"
#include "../../reserved-keywords/reserved-keywords.h"

class LexicalAnalyzer {
private:
    FileReader _fileReader;
    ReservedKeywords _reservedKeywords;
    bool _hasMore;
    std::optional<Token*> buildNextToken();
    int getNextLine();
    int getNextPosition();
    void skipWhitespaceAndNewLine();
    void stopIfNecessary();
public:
    LexicalAnalyzer();
    void start(std::string &filePath);
    void stop();
    std::optional<Lexeme> next();
    bool hasMore() const;
};

#endif //JETLANG_LEXICAL_ANALYZER_H
