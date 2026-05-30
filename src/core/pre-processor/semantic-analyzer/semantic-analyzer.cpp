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
    auto typeSignatureContext = new TypeSignatureContext();
    auto declarations = std::vector<ASTDeclarationNode*>();
    for (auto node : *fileNode->getBody()) {
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            _typeSignatureGenerator->assignTypeSignatureFor(node, typeSignatureContext, scope);
        } else if (ASTNodeUtils::isDeclarableNode(node)) {
            auto declarationNode = (ASTDeclarationNode*)node;
            _typeSignatureGenerator->assignInitialTypeSignatureFor(declarationNode, typeSignatureContext, scope);
            declarationNode->getTypeSignature()->setId(declarationNode->getId());
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
            declarations.push_back((ASTDeclarationNode*)node);
        }
    }

    for (auto declarationNode : declarations) {
        _typeSignatureGenerator->assignPostInitialTypeSignatureFor(declarationNode, typeSignatureContext, scope);
    }
}

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    auto typeSignatureContext = new TypeSignatureContext();
    for (auto node : *fileNode->getBody()) {
        _typeSignatureGenerator->assignTypeSignatureFor(node, typeSignatureContext, fileScope);
        if (ASTNodeUtils::isDeclarableNode(node)) {
            fileScope->find(fileNode->getModuleName(), node->getId())->copyFrom(node->getTypeSignature());
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