//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../shared/utils/logger/logger.h"

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
    fileNode->getBody()->hoistTypes({ AST_ENUM_DECLARATION_NODE, AST_FUNCTION_DECLARATION_NODE });
    for (auto node : fileNode->getBody()->getContents()) {
        _declarationIdAssignor->assignId(node);
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            _typeSignatureLookupTable->insert(
                node->getId(),
                _typeSignatureGenerator
                ->generateInitialTypeSignatureForTypeDeclaration((ASTDeclarationNode*) node)
            );
        }
    }

    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(node)) {
            auto declarationTypeSignature = _typeSignatureGenerator->generateTypeSignatureForDeclaration((ASTDeclarationNode*)node);
            if (ASTNodeUtils::isTypeDeclarationNode(node)) {
                _typeSignatureLookupTable->find(node->getId())->copyFrom(declarationTypeSignature);
            } else {
                _typeSignatureLookupTable->insert(node->getId(), declarationTypeSignature);
            }
        }
    }
}

void SemanticAnalyzer::runTypeCheckerOn(ASTFileNode* fileNode) {
    // build type checker and execute it here.
}