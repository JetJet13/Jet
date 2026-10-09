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
