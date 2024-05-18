//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_SEMANTIC_ANALYZER_H
#define JETLANG_SEMANTIC_ANALYZER_H

#include "dependency-graph/dependency-graph.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "declaration-id-assignor/declaration-id-assignor.h"
#include "type-signature-lookup-table/type-signature-lookup-table.h"
#include "type-signature-generator/type-signature-generator.h"


class SemanticAnalyzer {
private:
    DependencyGraph* _dependencyGraph;
    TokenTable* _tokenTable;
    DeclarationIdAssignor* _declarationIdAssignor;
    TypeSignatureGenerator* _typeSignatureGenerator;
    void prepareDeclarationsFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
    void runTypeCheckerOn(ASTFileNode* fileNode);
public:
    SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable);
    void analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
