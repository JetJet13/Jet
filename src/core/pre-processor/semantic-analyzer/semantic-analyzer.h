//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_SEMANTIC_ANALYZER_H
#define JETLANG_SEMANTIC_ANALYZER_H

#include "dependency-graph/dependency-graph.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "type-signature-lookup-table/type-signature-lookup-table.h"
#include "type-signature-generator/type-signature-generator.h"


class SemanticAnalyzer {
private:
    DependencyGraph* _dependencyGraph;
    TypeSignatureGenerator* _typeSignatureGenerator;
    void generateInitialTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
    void generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
    void runTypeCheckerOn(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
public:
    SemanticAnalyzer(DependencyGraph* dependencyGraph);
    void analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
