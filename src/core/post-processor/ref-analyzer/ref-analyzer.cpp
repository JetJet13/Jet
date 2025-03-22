//
// Created by Johny Georges on 2025-03-22.
//

#include "ref-analyzer.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"

RefAnalyzer::RefAnalyzer() {
    _astTraverser = ASTTraverser();
}

void RefAnalyzer::analyze(ASTDeclarationNode* node, ASTLookupTable* scope) {
    if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
        this->analyze((ASTVariableDeclarationNode*)node, scope);
    } else if (node->is(AST_FUNCTION_DECLARATION_NODE)) {
        this->analyze((ASTFunctionDeclarationNode*)node, scope);
    } else if (node->is(AST_PROCEDURE_DECLARATION_NODE)) {
        this->analyze((ASTProcedureDeclarationNode*)node, scope);
    }
}

void RefAnalyzer::analyze(ASTVariableDeclarationNode* node, ASTLookupTable* scope) {
    _astTraverser.init(node->getInitializerNode());
    auto expressionNode = _astTraverser.next();
    while (expressionNode) {
        auto expression = expressionNode.value();
        if (expression->is(AST_REF_EXPRESSION_NODE)) {
            auto refExpression = (ASTRefExpressionNode*)expression;
            refExpression->getExpressionNode()->markAsReferenced();
            if (refExpression->getExpressionNode()->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
                auto idExpression = (ASTIdentifierExpressionNode*)refExpression->getExpressionNode();
                auto referencedVariable = (ASTVariableDeclarationNode*)scope->findAcrossScopes(idExpression->getId()).value();
                referencedVariable->markAsReferenced();
            }
        }
        expressionNode = _astTraverser.next();
    }

}

void RefAnalyzer::analyze(ASTFunctionDeclarationNode* functionNode, ASTLookupTable* scope) {
    for (auto node : *functionNode->getBlock()->getContents()) {
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            auto variable = (ASTVariableDeclarationNode*)node;
            scope->insert(node->getId(), variable);
            this->analyze(variable, scope);
        }
    }
}

void RefAnalyzer::analyze(ASTProcedureDeclarationNode* procedureNode, ASTLookupTable* scope) {
    for (auto node : *procedureNode->getBlock()->getContents()) {
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            auto variable = (ASTVariableDeclarationNode*)node;
            scope->insert(node->getId(), variable);
            this->analyze(variable, scope);
        }
    }
}