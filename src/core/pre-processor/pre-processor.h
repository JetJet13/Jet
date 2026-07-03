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
    ScopeAnalyzer _scopeAnalyzer;
    std::shared_ptr<SyntaxAnalyzer> _syntaxAnalyzer;
    std::shared_ptr<SemanticAnalyzer> _semanticAnalyzer;
    std::shared_ptr<ASTFileNode> buildFile(std::string filePath, std::shared_ptr<FileScope> fileScope);
    std::set<JetFile*> resolveModuleImports(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope);
public:
    PreProcessor(std::shared_ptr<SyntaxAnalyzer> syntaxAnalyzer, std::shared_ptr<SemanticAnalyzer> semanticAnalyzer);
    JetFile* process(std::string filePath);
};

#endif //JETLANG_PRE_PROCESSOR_H
