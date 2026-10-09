// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

void SyntaxAnalyzerResult::printErrors(std::string filePath) {
    Logger::log("\n");
    auto canonicalPath = std::filesystem::canonical(filePath).string();
    for (auto syntaxError : _syntaxErrors) {
        Logger::log("File", canonicalPath);
        Logger::log("SyntaxError", syntaxError);
    }
    Logger::log("\n");
}