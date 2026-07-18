//
// Created by Johny Georges on 2025-07-19.
//

#ifndef JETLANG_SYNTAX_ANALYZER_RESULT_H
#define JETLANG_SYNTAX_ANALYZER_RESULT_H

#include "../file-scope/file-scope.h"

class SyntaxAnalyzerResult {
private:
    std::shared_ptr<FileScope> _fileScope;
    std::vector<std::string> _syntaxErrors;
public:
    SyntaxAnalyzerResult(std::shared_ptr<FileScope> fileScope, std::vector<std::string> syntaxErrors);
    std::shared_ptr<FileScope> getFileScope();
    std::vector<std::string>* getErrors();
    bool ok();
    void printErrors(std::string filePath);
};

#endif //JETLANG_SYNTAX_ANALYZER_RESULT_H
