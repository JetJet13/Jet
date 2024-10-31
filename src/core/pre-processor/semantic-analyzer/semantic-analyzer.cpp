//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "ast-traverser/ast-traverser.h"

SemanticAnalyzer::SemanticAnalyzer(DependencyGraph* dependencyGraph, SyntaxAnalyzer* syntaxAnalyzer) {
    _dependencyGraph = dependencyGraph;
    _syntaxAnalyzer = syntaxAnalyzer;
    _typeSignatureGenerator = new TypeSignatureGenerator(
        new TypeSignatureStrategyProvider()
    );
}

TypeCheckerResult SemanticAnalyzer::analyze(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    auto typeCheckerResult = TypeCheckerResult();
    this->resolveModuleImports(fileNode, fileScope, &typeCheckerResult);
    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope);
    this->generateTypeSignatureForModule(fileNode, fileScope);
    this->runTypeChecker(fileNode, &typeCheckerResult);
    return typeCheckerResult;
}

void SemanticAnalyzer::resolveModuleImports(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope, TypeCheckerResult* typeCheckerResult) {
    for (auto node : *fileNode->getBody()) {
        if (node->is(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE)) {
            auto filePath = fileNode->getPathDirectory().append(
                    ((ASTImportSingleModuleDeclarationNode*)node)->getPath()->getImportPath()->getValue());
            Logger::log("filePath", filePath);
            auto importFile = this->_syntaxAnalyzer->analyze(filePath);
            auto importModuleTypeCheckerResult = this->analyze(importFile, new TypeSignatureLookupTable());
            typeCheckerResult->combine(importModuleTypeCheckerResult);
        }
    }
}

void SemanticAnalyzer::generateInitialTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
    for (auto node : *fileNode->getBody()) {
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            scope->insert(
                    node->getId(),
                    _typeSignatureGenerator
                    ->generateInitialTypeSignatureForTypeDeclaration((ASTDeclarationNode*) node)
            );
        }
    }
}

void SemanticAnalyzer::generateDeclarationTypeSignaturesFor(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    for (auto node : *fileNode->getBody()) {
        _typeSignatureGenerator->assignTypeSignatureFor(node, fileScope);
        if (ASTNodeUtils::isTypeDeclarationNode(node)) {
            fileScope->find(node->getId())->copyFrom(node->getTypeSignature());
        }
    }
}

void SemanticAnalyzer::generateTypeSignatureForModule(ASTFileNode* fileNode, TypeSignatureLookupTable* fileScope) {
    if (fileNode->getModule()) {
        _typeSignatureGenerator->assignTypeSignatureFor(fileNode->getModule().value(), fileScope);
    }
}

void SemanticAnalyzer::runTypeChecker(ASTFileNode* fileNode, TypeCheckerResult* typeCheckerResults) {
    for (auto node : *fileNode->getBody()) {
        TypeChecker::applyPolicyTo(node, typeCheckerResults);
    }
}