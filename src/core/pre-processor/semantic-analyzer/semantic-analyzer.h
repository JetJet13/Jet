//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_SEMANTIC_ANALYZER_H
#define JETLANG_SEMANTIC_ANALYZER_H

#include "dependency-graph/dependency-graph.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "declaration-id-assignor/declaration-id-assignor.h"
#include "type-signature-lookup-table/type-signature-lookup-table.h"


class SemanticAnalyzer {
private:
    DependencyGraph* _dependencyGraph;
    TypeSignatureLookupTable* _typeSignatureLookupTable;
    TokenTable* _tokenTable;
    DeclarationIdAssignor* _declarationIdAssignor;
    int generateDeclarationId();
    void assignDeclarationIds(ASTFileNode* fileNode);
public:
    SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable);
    void analyze(ASTFileNode* fileNode);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
