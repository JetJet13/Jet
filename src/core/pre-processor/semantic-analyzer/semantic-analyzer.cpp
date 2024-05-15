//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable, TypeSignatureLookupTable* typeSignatureLookupTable) {
    _dependencyGraph = dependencyGraph;
    _tokenTable = tokenTable;
    _typeSignatureLookupTable = typeSignatureLookupTable;
    _declarationIdAssignor = new DeclarationIdAssignor(_tokenTable);
    _typeSignatureGenerator = new TypeSignatureGenerator(
        new TypeSignatureStrategyProvider(_typeSignatureLookupTable, _tokenTable)
    );
}

void SemanticAnalyzer::analyze(ASTFileNode* fileNode) {
    this->prepareDeclarationsFor(fileNode);
    this->runTypeCheckerOn(fileNode);
}

void SemanticAnalyzer::prepareDeclarationsFor(ASTFileNode* fileNode) {
    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(node)) {

            // step 1: generate id for each declaration
            // step 2: create a mapping between id and declaration
            // step 3: traverse AST and determine type-signature:
            //  1. generate it OR
            //  2. look-up type-signature in lookup table:
            //     if type-signature exists, assign it
            //     otherwise, determine it


            // step 1: create a declaration id to assign to ast declaration node
            _declarationIdAssignor->assignId(node);

            // step 2: determine type signature for declaration
            auto declarationTypeSignature = _typeSignatureGenerator->generateTypeSignatureForDeclaration((ASTDeclarationNode*)node);

            // step 3: add declaration id -> declaration type signature to type-signature-lookup-table
            _typeSignatureLookupTable->insert(node->getId(), declarationTypeSignature);
        }
    }
}

void SemanticAnalyzer::runTypeCheckerOn(ASTFileNode* fileNode) {
    // build type checker and execute it here.
}