//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../shared/utils/logger/logger.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph, TokenTable* tokenTable) {
    _dependencyGraph = dependencyGraph;
    _tokenTable = tokenTable;
    _declarationIdAssignor = new DeclarationIdAssignor(_tokenTable);
    _typeSignatureGenerator = new TypeSignatureGenerator(
        new TypeSignatureStrategyProvider(_tokenTable)
    );
}

void SemanticAnalyzer::analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
    this->prepareDeclarationsFor(fileNode, scope);
    this->runTypeCheckerOn(fileNode);
}

void SemanticAnalyzer::prepareDeclarationsFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
    for (auto node : fileNode->getBody()->getContents()) {
        _declarationIdAssignor->assignId(node);
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            scope->insert(
                node->getId(),
                _typeSignatureGenerator
                ->generateInitialTypeSignatureForTypeDeclaration((ASTDeclarationNode*) node)
            );
        }
    }

    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(node)) {
            auto declarationTypeSignature = _typeSignatureGenerator->generateTypeSignatureForDeclaration((ASTDeclarationNode*)node, scope);
            if (ASTNodeUtils::isTypeDeclarationNode(node)) {
                scope->find(node->getId())->copyFrom(declarationTypeSignature);
            } else {
                scope->insert(node->getId(), declarationTypeSignature);
            }
        }
    }
}

void SemanticAnalyzer::runTypeCheckerOn(ASTFileNode* fileNode) {
    // build type checker and execute it here.
}