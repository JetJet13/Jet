//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-traverser/ast-traverser.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph) {
    _dependencyGraph = dependencyGraph;
    _typeSignatureGenerator = new TypeSignatureGenerator(
        new TypeSignatureStrategyProvider()
    );
}

void SemanticAnalyzer::analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope);
    this->runTypeCheckerOn(fileNode, fileScope);
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

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
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

void SemanticAnalyzer::runTypeCheckerOn(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    // build type checker and execute it here.
    auto traverser = ASTTraverser();
    traverser.init(fileNode);
    auto node = traverser.next();
    while (node) {
        Logger::log("type-checker---", node.value()->toString());
        node = traverser.next();
    }
}