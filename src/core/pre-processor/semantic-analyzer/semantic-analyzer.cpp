//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "ast-traverser/ast-traverser.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph) {
    _dependencyGraph = dependencyGraph;
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
    for (auto node : *fileNode->getBody()->getContents()) {
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
    for (auto node : *fileNode->getBody()->getContents()) {
        _typeSignatureGenerator->assignTypeSignatureFor(node, fileScope);
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            fileScope->find(node->getId())->copyFrom(node->getTypeSignature());
        } else if (ASTNodeUtils::isDeclarationNode(node)){
            fileScope->insert(node->getId(), node->getTypeSignature());
        }
        auto typeCheckerResult = TypeCheckerResult();
        TypeChecker::applyPolicyTo(node, &typeCheckerResult);
        typeCheckerResult.print();
        typeCheckerResults->push_back(typeCheckerResult);
    }
}