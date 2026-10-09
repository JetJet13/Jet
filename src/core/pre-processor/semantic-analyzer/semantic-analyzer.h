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
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_SEMANTIC_ANALYZER_H
#define JETLANG_SEMANTIC_ANALYZER_H

#include "../../ast/ast-nodes/ast-file-node.h"
#include "type-signature-lookup-table/type-signature-lookup-table.h"
#include "type-signature-generator/type-signature-generator.h"
#include "types/ast-node-type-signature-result.h"
#include "type-checker/type-checker.h"
#include "type-checker/types/type-checker-result/type-checker-result.h"
#include "../syntax-analyzer/syntax-analyzer.h"

class SemanticAnalyzer {
private:
    bool _debugMode;
    TypeSignatureGenerator _typeSignatureGenerator;
    void generateInitialTypeSignaturesFor(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope);
    void generateDeclarationTypeSignaturesFor(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope);
    void generateTypeSignatureForModule(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope);
    void runTypeChecker(std::shared_ptr<ASTFileNode> fileNode, TypeCheckerResult* typeCheckerResults, std::shared_ptr<TypeSignatureLookupTable> fileScope);
public:
    SemanticAnalyzer();
    void switchToDebugMode();
    TypeCheckerResult analyze(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
