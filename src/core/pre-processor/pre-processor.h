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
    SyntaxAnalyzer* _syntaxAnalyzer;
    SemanticAnalyzer* _semanticAnalyzer;
    ASTFileNode* buildFile(std::string filePath, FileScope* fileScope);
    std::set<JetFile*> resolveModuleImports(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
public:
    PreProcessor(SyntaxAnalyzer* syntaxAnalyzer, SemanticAnalyzer* semanticAnalyzer);
    JetFile* process(std::string filePath);
};

#endif //JETLANG_PRE_PROCESSOR_H
