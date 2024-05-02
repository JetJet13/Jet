//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_SEMANTIC_ANALYZER_H
#define JETLANG_SEMANTIC_ANALYZER_H

#include "dependency-graph/dependency-graph.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "declaration-id-generator/declaration-id-generator.h"

class SemanticAnalyzer {
private:
    DependencyGraph* _dependencyGraph;
    TokenTable* _tokenTable;
    DeclarationIdGenerator* _declarationIdGenerator;
    int generateDeclarationId();
    void assignDeclarationIds(ASTFileNode* fileNode);
public:
    SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable);
    void analyze(ASTFileNode* fileNode);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
