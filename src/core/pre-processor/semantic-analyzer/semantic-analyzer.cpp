//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

SemanticAnalyzer::SemanticAnalyzer() {
    _typeSignatureGenerator = new TypeSignatureGenerator(
        new TypeSignatureStrategyProvider()
    );
}

TypeCheckerResult SemanticAnalyzer::analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    auto typeCheckerResult = TypeCheckerResult();
    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope);
    this->generateTypeSignatureForModule(fileNode, fileScope);
    this->runTypeChecker(fileNode, &typeCheckerResult);
    return typeCheckerResult;
}


void SemanticAnalyzer::generateInitialTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
    auto typeDeclarations = std::vector<ASTDeclarationNode*>();
    for (auto node : *fileNode->getBody()) {
        if (ASTNodeUtils::isDeclarableNode(node)) {
            typeDeclarations.push_back((ASTDeclarationNode*)node);
        }
    }

    auto typeSignatureContext = new TypeSignatureContext();
    for (auto declarationNode : typeDeclarations) {
        _typeSignatureGenerator->assignInitialTypeSignatureForDeclaration(declarationNode, typeSignatureContext, scope);
        if (declarationNode->getTypeSignature()->isInvocable()) {
            scope->insertGlobalInvocable(
                declarationNode->getId(),
                (InvocableTypeSignature*)declarationNode->getTypeSignature()
            );
        } else {
            scope->insertGlobal(
                    declarationNode->getId(),
                    declarationNode->getTypeSignature()
            );
        }
    }

    for (auto declarationNode : typeDeclarations) {
        _typeSignatureGenerator->assignPartialTypeSignatureForTypeDeclaration(declarationNode, typeSignatureContext, scope);
    }
}

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    auto typeSignatureContext = new TypeSignatureContext();
    for (auto node : *fileNode->getBody()) {
        _typeSignatureGenerator->assignTypeSignatureFor(node, typeSignatureContext, fileScope);
        if (ASTNodeUtils::isDeclarableNode(node)) {
            fileScope->find(node->getId())->copyFrom(node->getTypeSignature());
        }
    }
}

void SemanticAnalyzer::generateTypeSignatureForModule(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    if (fileNode->getModule()) {
        _typeSignatureGenerator->assignTypeSignatureFor(fileNode->getModule().value(), new TypeSignatureContext(), fileScope);
    }
}

void SemanticAnalyzer::runTypeChecker(ASTFileNode* fileNode, TypeCheckerResult* typeCheckerResults) {
    for (auto node : *fileNode->getBody()) {
        TypeChecker::applyPolicyTo(node, typeCheckerResults);
    }
}