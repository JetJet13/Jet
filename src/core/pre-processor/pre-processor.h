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
// Created by Johny Georges on 2024-11-04.
//

#ifndef JETLANG_PRE_PROCESSOR_H
#define JETLANG_PRE_PROCESSOR_H

#include <string>
#include "../ast/ast-nodes/ast-file-node.h"
#include "semantic-analyzer/semantic-analyzer.h"
#include "lexical-analyzer/lexical-analyzer.h"
#include "../jet-file/jet-file.h"
#include "pre-processor-map/pre-processor-map.h"
#include "scope-analyzer/scope-analyzer.h"

class PreProcessor {
private:
    PreProcessorMap _processedFileMap;
    TypeCheckerResult _typeCheckerResult;
    ScopeAnalyzer _scopeAnalyzer;
    bool _debugMode;
    std::shared_ptr<SyntaxAnalyzer> _syntaxAnalyzer;
    std::shared_ptr<SemanticAnalyzer> _semanticAnalyzer;
    std::shared_ptr<ASTFileNode> buildFile(std::string filePath, std::shared_ptr<FileScope> fileScope);
    std::set<std::shared_ptr<JetFile>> resolveModuleImports(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope);
public:
    PreProcessor(std::shared_ptr<SyntaxAnalyzer> syntaxAnalyzer, std::shared_ptr<SemanticAnalyzer> semanticAnalyzer);
    void switchToDebugMode();
    TypeCheckerResult* getTypeCheckerResult();
    std::shared_ptr<JetFile> process(std::string filePath);
};

#endif //JETLANG_PRE_PROCESSOR_H
