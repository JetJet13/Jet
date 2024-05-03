//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable) {
    _dependencyGraph = dependencyGraph;
    _tokenTable = tokenTable;
    _declarationIdAssignor = new DeclarationIdAssignor(_tokenTable);
    _typeSignatureLookupTable = new TypeSignatureLookupTable();
}

void SemanticAnalyzer::analyze(ASTFileNode* fileNode) {
    this->assignDeclarationIds(fileNode);
}

void SemanticAnalyzer::assignDeclarationIds(ASTFileNode* fileNode) {
    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(node)) {
            // step 1: create a declaration id to assign to ast declaration node
            _declarationIdAssignor->assignId(node);

            // step 2: determine type signature for declaration

            // step 3: add declaration id -> declaration type signature to type-signature-lookup-table

        }
    }
}