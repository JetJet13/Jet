//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-traverser/ast-traverser.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph) {
    _dependencyGraph = dependencyGraph;
    _typeChecker = TypeChecker();
    _typeSignatureGenerator = new TypeSignatureGenerator(
        new TypeSignatureStrategyProvider()
    );
}

std::vector<TypeCheckerResult> SemanticAnalyzer::analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    auto typeCheckerResults = std::vector<TypeCheckerResult>();
    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope, &typeCheckerResults);
    return typeCheckerResults;
}

void SemanticAnalyzer::generateInitialTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            scope->insert(
                    node->getId(),
                    _typeSignatureGenerator
                            ->generateInitialTypeSignatureForTypeDeclaration((ASTDeclarationNode*) node)
            );
        }
    }
}

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope, std::vector<TypeCheckerResult>* typeCheckerResults) {
    for (auto node : fileNode->getBody()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(node)) {
            auto declarationNode = (ASTDeclarationNode*)node;
            _typeSignatureGenerator->assignTypeSignatureForDeclaration(declarationNode, fileScope);
            if (ASTNodeUtils::isTypeDeclarationNode(node)) {
                fileScope->find(node->getId())->copyFrom(declarationNode->getTypeSignature());
            } else {
                fileScope->insert(node->getId(), declarationNode->getTypeSignature());
            }
            typeCheckerResults->push_back(_typeChecker.check(node, fileScope));
        }
    }
}