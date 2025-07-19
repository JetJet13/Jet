//
// Created by Johny Georges on 2025-07-19.
//

#ifndef JETLANG_SYNTAX_ANALYZER_RESULT_H
#define JETLANG_SYNTAX_ANALYZER_RESULT_H

#include "../file-scope/file-scope.h"

class SyntaxAnalyzerResult {
private:
    FileScope* _fileScope;
    std::vector<std::string> _syntaxErrors;
public:
    SyntaxAnalyzerResult(FileScope* fileScope, std::vector<std::string> syntaxErrors);
    FileScope* getFileScope();
    std::vector<std::string>* getErrors();
    bool ok();
    void printErrors();
};

#endif //JETLANG_SYNTAX_ANALYZER_RESULT_H
