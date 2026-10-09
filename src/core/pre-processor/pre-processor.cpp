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

#include "pre-processor.h"
#include "../jet-file/jet-file-id-generator/jet-file-id-generator.h"
#include "semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table-factory.h"
#include "../../shared/types/exit-status.enum.h"

PreProcessor::PreProcessor(std::shared_ptr<SyntaxAnalyzer> syntaxAnalyzer, std::shared_ptr<SemanticAnalyzer> semanticAnalyzer) {
    _processedFileMap = PreProcessorMap();
    _typeCheckerResult = TypeCheckerResult();
    _scopeAnalyzer = ScopeAnalyzer();
    _syntaxAnalyzer = syntaxAnalyzer;
    _semanticAnalyzer = semanticAnalyzer;
    _debugMode = false;
}

std::shared_ptr<ASTFileNode> PreProcessor::buildFile(std::string filePath, std::shared_ptr<FileScope> fileScope) {
    auto fileNode = std::make_shared<ASTFileNode>(std::move(fileScope->getScope()), filePath, fileScope->getImports(), fileScope->getModule());
    fileNode->markGlobalVariables();
    fileNode->hoistTypes({ AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE });
    fileNode->setupModuleIfNecessary();
    return fileNode;
}

void PreProcessor::switchToDebugMode() {
    _debugMode = true;
    _syntaxAnalyzer->switchToDebugMode();
    _semanticAnalyzer->switchToDebugMode();
    _scopeAnalyzer.switchToDebugMode();
}

TypeCheckerResult* PreProcessor::getTypeCheckerResult() {
    return &_typeCheckerResult;
}

std::shared_ptr<JetFile> PreProcessor::process(std::string filePath) {
    auto processedFile = _processedFileMap.findByFilePath(filePath);
    if (processedFile) {
        return processedFile.value();
    }
    auto syntaxResult = _syntaxAnalyzer->analyze(filePath);
    if (!syntaxResult->ok()) {
        syntaxResult->printErrors(filePath);
        exit(EXIT_STATUS_GENERIC_ERROR);
    }
    auto fileNode = this->buildFile(filePath, syntaxResult->getFileScope());
    _scopeAnalyzer.process(fileNode);
    auto typeSignatureScope = _debugMode
            ? TypeSignatureLookupTableFactory::createForDebugModule(fileNode->getModuleName())
            : TypeSignatureLookupTableFactory::createForModule(fileNode->getModuleName());
    auto importedJetFiles = this->resolveModuleImports(fileNode, typeSignatureScope);
    auto typeCheckerResult = _semanticAnalyzer->analyze(fileNode, typeSignatureScope);
    auto jetFile = std::make_shared<JetFile>(fileNode, typeSignatureScope, typeCheckerResult, importedJetFiles);
    _processedFileMap.insert(jetFile);
    _typeCheckerResult.merge(jetFile->getTypeCheckerResult());
    return jetFile;
}

std::set<std::shared_ptr<JetFile>> PreProcessor::resolveModuleImports(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope) {
    auto importedJetFiles = std::set<std::shared_ptr<JetFile>>();
    for (auto node : *fileNode->getImports()) {
        auto filePath = fileNode->getPathDirectory().append(node->getPath()->getImportPath()->getValue());
        auto jetFile = this->process(filePath);
        if (!jetFile->isModule()) {
            throw std::logic_error("cannot import a file that is not a module: " + jetFile->getId());
        }
        scope->link(jetFile->getScope());
        importedJetFiles.insert(jetFile);
    }
    return importedJetFiles;
}