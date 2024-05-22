//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_SEMANTIC_ANALYZER_H
#define JETLANG_SEMANTIC_ANALYZER_H

#include "dependency-graph/dependency-graph.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "type-signature-lookup-table/type-signature-lookup-table.h"
#include "type-signature-generator/type-signature-generator.h"
#include "types/ast-node-type-signature-result.h"
#include "type-checker/type-checker.h"

class SemanticAnalyzer {
private:
    DependencyGraph* _dependencyGraph;
    TypeSignatureGenerator* _typeSignatureGenerator;
    TypeChecker _typeChecker;
    void generateInitialTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
    void generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope, std::vector<TypeCheckerResult>* typeCheckerResults);
    void runTypeCheckerOn(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
public:
    SemanticAnalyzer(DependencyGraph* dependencyGraph);
    std::vector<TypeCheckerResult> analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
