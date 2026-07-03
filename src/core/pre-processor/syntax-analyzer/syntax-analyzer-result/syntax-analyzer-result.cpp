//
// Created by Johny Georges on 2025-07-19.
//

#include "syntax-analyzer-result.h"
#include "../../../../shared/utils/logger/logger.h"

SyntaxAnalyzerResult::SyntaxAnalyzerResult(std::shared_ptr<FileScope> fileScope, std::vector<std::string> syntaxErrors) {
    _fileScope = fileScope;
    _syntaxErrors = syntaxErrors;
}

std::shared_ptr<FileScope> SyntaxAnalyzerResult::getFileScope() {
    return _fileScope;
}

std::vector<std::string>* SyntaxAnalyzerResult::getErrors() {
    return &_syntaxErrors;
}

bool SyntaxAnalyzerResult::ok() {
    return _syntaxErrors.empty();
}

void SyntaxAnalyzerResult::printErrors() {
    for (auto syntaxError : _syntaxErrors) {
        Logger::log("SyntaxError", syntaxError);
    }
}