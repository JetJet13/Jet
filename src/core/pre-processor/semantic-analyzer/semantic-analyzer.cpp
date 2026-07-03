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

TypeCheckerResult SemanticAnalyzer::analyze(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto typeCheckerResult = TypeCheckerResult();

    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope);
    this->generateTypeSignatureForModule(fileNode, fileScope);
    this->runTypeChecker(fileNode, &typeCheckerResult);
    return typeCheckerResult;
}
// TODO - continue shared_ptr migration by replacing 'scope.get()' with scope
void SemanticAnalyzer::generateInitialTypeSignaturesFor(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope) {
    auto typeSignatureContext = new TypeSignatureContext();
    auto declarations = std::vector<ASTDeclarationNode*>();
    for (auto node : *fileNode->getBody()) {
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            _typeSignatureGenerator->assignTypeSignatureFor(node, typeSignatureContext, scope.get());
        } else if (ASTNodeUtils::isDeclarableNode(node)) {
            auto declarationNode = (ASTDeclarationNode*)node;
            _typeSignatureGenerator->assignInitialTypeSignatureFor(declarationNode, typeSignatureContext, scope.get());
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
        _typeSignatureGenerator->assignPostInitialTypeSignatureFor(declarationNode, typeSignatureContext, scope.get());
    }
}

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto typeSignatureContext = new TypeSignatureContext();
    for (auto node : *fileNode->getBody()) {
        _typeSignatureGenerator->assignTypeSignatureFor(node, typeSignatureContext, fileScope.get());
        if (ASTNodeUtils::isDeclarableNode(node)) {
            fileScope->find(fileNode->getModuleName(), node->getId())->copyFrom(node->getTypeSignature());
        }
    }
}

void SemanticAnalyzer::generateTypeSignatureForModule(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    if (fileNode->getModule()) {
        _typeSignatureGenerator->assignTypeSignatureFor(fileNode->getModule().value(), new TypeSignatureContext(), fileScope.get());
    }
}

void SemanticAnalyzer::runTypeChecker(std::shared_ptr<ASTFileNode> fileNode, TypeCheckerResult* typeCheckerResults) {
    for (auto node : *fileNode->getBody()) {
        TypeChecker::applyPolicyTo(node, typeCheckerResults);
    }
}