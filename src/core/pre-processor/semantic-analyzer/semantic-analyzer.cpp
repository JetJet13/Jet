//
// Created by Johny Georges on 2024-05-01.
//

#include "semantic-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "type-checker/rules/type-checker-rule-provider.h"
#include "../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

SemanticAnalyzer::SemanticAnalyzer() {
    _typeSignatureGenerator = TypeSignatureGenerator();
}

TypeCheckerResult SemanticAnalyzer::analyze(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto typeCheckerResult = TypeCheckerResult();

    this->generateInitialTypeSignaturesFor(fileNode, fileScope);
    this->generateDeclarationTypeSignaturesFor(fileNode, fileScope);
    this->generateTypeSignatureForModule(fileNode, fileScope);
    this->runTypeChecker(fileNode, &typeCheckerResult, fileScope);
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

void SemanticAnalyzer::runTypeChecker(std::shared_ptr<ASTFileNode> fileNode, TypeCheckerResult* typeCheckerResults, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto variableDeclarations = std::vector<std::shared_ptr<ASTVariableDeclarationNode>>();
    auto functionDeclarations = std::vector<std::shared_ptr<ASTFunctionDeclarationNode>>();
    auto procedureDeclarations = std::vector<std::shared_ptr<ASTProcedureDeclarationNode>>();
    auto classDeclarations = std::vector<std::shared_ptr<ASTClassDeclarationNode>>();
    auto enumDeclarations = std::vector<std::shared_ptr<ASTEnumDeclarationNode>>();
    auto customTypeDeclarations = std::vector<std::shared_ptr<ASTCustomTypeDeclarationNode>>();
    for (auto node : *fileNode->getBody()) {
        TypeChecker::applyPolicyTo(node, typeCheckerResults, fileScope);
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            variableDeclarations.push_back(std::dynamic_pointer_cast<ASTVariableDeclarationNode>(node));
        }
        if (node->is(AST_FUNCTION_DECLARATION_NODE)) {
            functionDeclarations.push_back(std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(node));
        }
        if (node->is(AST_PROCEDURE_DECLARATION_NODE)) {
            procedureDeclarations.push_back(std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node));
        }
        if (node->is(AST_CLASS_DECLARATION_NODE)) {
            classDeclarations.push_back(std::dynamic_pointer_cast<ASTClassDeclarationNode>(node));
        }
        if (node->is(AST_ENUM_DECLARATION_NODE)) {
            enumDeclarations.push_back(std::dynamic_pointer_cast<ASTEnumDeclarationNode>(node));
        }
        if (node->is(AST_CUSTOM_TYPE_DECLARATION_NODE)) {
            customTypeDeclarations.push_back(std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(node));
        }
    }
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &variableDeclarations,
        typeCheckerResults
    );
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &functionDeclarations,
        typeCheckerResults
    );
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &procedureDeclarations,
        typeCheckerResults
    );
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &classDeclarations,
        typeCheckerResults
    );
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &enumDeclarations,
        typeCheckerResults
    );
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &customTypeDeclarations,
        typeCheckerResults
    );
}