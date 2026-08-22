//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "type-checker/rules/type-checker-rule-provider.h"

SemanticAnalyzer::SemanticAnalyzer() {
    _typeSignatureGenerator = TypeSignatureGenerator();
}

TypeCheckerResult SemanticAnalyzer::analyze(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto typeCheckerResult = TypeCheckerResult();

    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope);
    this->generateTypeSignatureForModule(fileNode, fileScope);
    this->runTypeChecker(fileNode, &typeCheckerResult);
    return typeCheckerResult;
}

void SemanticAnalyzer::generateInitialTypeSignaturesFor(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope) {
    auto typeSignatureContext = std::make_shared<TypeSignatureContext>();
    auto declarations = std::vector<std::shared_ptr<ASTDeclarationNode>>();
    for (auto node : *fileNode->getBody()) {
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            _typeSignatureGenerator.assignTypeSignatureFor(node, typeSignatureContext, scope);
        } else if (ASTNodeUtils::isDeclarableNode(node)) {
            auto declarationNode = std::dynamic_pointer_cast<ASTDeclarationNode>(node);
            _typeSignatureGenerator.assignInitialTypeSignatureFor(declarationNode, typeSignatureContext, scope);
            declarationNode->getTypeSignature()->setId(declarationNode->getId());
            if (declarationNode->getTypeSignature()->isInvocable()) {
                scope->insertGlobalInvocable(
                    declarationNode->getId(),
                    std::dynamic_pointer_cast<InvocableTypeSignature>(declarationNode->getTypeSignature())
                );
            } else {
                scope->insertGlobal(
                    declarationNode->getId(),
                    declarationNode->getTypeSignature()
                );
            }
            declarations.push_back(std::dynamic_pointer_cast<ASTDeclarationNode>(node));
        }
    }

    for (auto declarationNode : declarations) {
        _typeSignatureGenerator.assignPostInitialTypeSignatureFor(declarationNode, typeSignatureContext, scope);
    }
}

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto typeSignatureContext = std::make_shared<TypeSignatureContext>();
    for (auto node : *fileNode->getBody()) {
        _typeSignatureGenerator.assignTypeSignatureFor(node, typeSignatureContext, fileScope);
        if (ASTNodeUtils::isDeclarableNode(node)) {
            fileScope->find(fileNode->getModuleName(), node->getId())->copyFrom(node->getTypeSignature());
        }
    }
}

void SemanticAnalyzer::generateTypeSignatureForModule(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    if (fileNode->getModule()) {
        _typeSignatureGenerator.assignTypeSignatureFor(fileNode->getModule().value(), std::make_shared<TypeSignatureContext>(), fileScope);
    }
}

void SemanticAnalyzer::runTypeChecker(std::shared_ptr<ASTFileNode> fileNode, TypeCheckerResult* typeCheckerResults) {
    auto variableDeclarations = std::vector<std::shared_ptr<ASTVariableDeclarationNode>>();
    for (auto node : *fileNode->getBody()) {
        TypeChecker::applyPolicyTo(node, typeCheckerResults);
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            variableDeclarations.push_back(std::dynamic_pointer_cast<ASTVariableDeclarationNode>(node));
        }
    }
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &variableDeclarations,
        typeCheckerResults
    );
}