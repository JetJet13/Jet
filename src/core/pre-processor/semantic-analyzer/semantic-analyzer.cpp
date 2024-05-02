//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-declaration-node.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable) {
    _dependencyGraph = dependencyGraph;
    _tokenTable = tokenTable;
    _declarationIdGenerator = new DeclarationIdGenerator(_tokenTable);
}

void SemanticAnalyzer::analyze(ASTFileNode* fileNode) {
    this->assignDeclarationIds(fileNode);
}

void SemanticAnalyzer::assignDeclarationIds(ASTFileNode* fileNode) {
    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(node)) {
            _declarationIdGenerator->generate(node);

        }
    }
}