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
    TypeSignatureGenerator* _typeSignatureGenerator;
    void generateInitialTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope);
    void generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
    void generateTypeSignatureForModule(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
    void runTypeChecker(ASTFileNode* fileNode, TypeCheckerResult* typeCheckerResults);
public:
    SemanticAnalyzer();
    TypeCheckerResult analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope);
};

#endif //JETLANG_SEMANTIC_ANALYZER_H
