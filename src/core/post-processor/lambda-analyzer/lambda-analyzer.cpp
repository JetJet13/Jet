//
// Created by Johny Georges on 2025-11-15.
//

#include "lambda-analyzer.h"

LambdaAnalyzer::LambdaAnalyzer() {
    _astTraverser = ASTTraverser();
}

void LambdaAnalyzer::analyzeLambdaReturnExpression(ASTLambdaReturnExpressionNode* lambdaReturnExpressionNode, ASTLookupTable* scope) {
    auto astTraverser = ASTTraverser();
    astTraverser.init(lambdaReturnExpressionNode->getExpression());
    auto nextNode = astTraverser.next();
    while (nextNode) {
        auto node = nextNode.value();
        if (node->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
            auto capturedNode = scope->find(node->getId());
            if (capturedNode.has_value() && capturedNode.value()->is(AST_VARIABLE_DECLARATION_NODE)) {
                auto capturedVariable = (ASTVariableDeclarationNode*)capturedNode.value();
                capturedVariable->markAsCaptured();
            }
        }
        nextNode = astTraverser.next();
    }
}

void LambdaAnalyzer::analyzeLambdaExpression(ASTLambdaExpressionNode* lambdaExpressionNode, ASTLookupTable* scope) {
    auto lambdaScope = new ASTLookupTable(scope);
    for (auto parameter : lambdaExpressionNode->getParameters()->getParameters()) {
        lambdaScope->insert(parameter->getIdentifier()->getId(), parameter);
    }
    auto astTraverser = ASTTraverser();
    astTraverser.init(lambdaExpressionNode->getBlock());
    auto nextNode = astTraverser.next();
    while (nextNode) {
        auto node = nextNode.value();
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            lambdaScope->insert(node->getId(), (ASTVariableDeclarationNode*)node);
        } else if (node->is(AST_IDENTIFIER_EXPRESSION_NODE) && !lambdaScope->findWithin(node->getId())) {
            auto capturedNode = scope->findInOuterScope(node->getId());
            if (capturedNode.has_value() && capturedNode.value()->is(AST_VARIABLE_DECLARATION_NODE)) {
                auto capturedVariable = (ASTVariableDeclarationNode*)capturedNode.value();
                capturedVariable->markAsCaptured();
            }
        }
        nextNode = astTraverser.next();
    }
}

void LambdaAnalyzer::analyze(ASTNode* nodeToAnalyze, ASTLookupTable* rootScope) {
    if (!nodeToAnalyze->isOneOf({ AST_FUNCTION_DECLARATION_NODE, AST_PROCEDURE_DECLARATION_NODE })) {
        return;
    }
    auto scope = new ASTLookupTable();
    scope->inherit(rootScope);
    auto scopeStack = std::stack<ASTLookupTable*>();
    scopeStack.push(scope);
    _astTraverser.init(nodeToAnalyze);
    auto nextNode = _astTraverser.next();
    auto currentScope = scopeStack.top();
    while (nextNode) {
        auto node = nextNode.value();
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            currentScope->insert(node->getId(), node);
        } else if (node->is(AST_FUNCTION_PARAMETER_NODE)) {
            auto functionParameter = (ASTFunctionParameterNode*)node;
            currentScope->insert(functionParameter->getIdentifier()->getId(), functionParameter);
        } else if (node->is(AST_CONTROL_FLOW_BLOCK_NODE)) {
            scopeStack.push(new ASTLookupTable(scope));
        } else if (node->is(AST_LAMBDA_EXPRESSION_NODE)) {
            this->analyzeLambdaExpression((ASTLambdaExpressionNode*)node, currentScope);
            auto lambdaScope = new ASTLookupTable(scope);
            scopeStack.push(lambdaScope);
        } else if (node->is(AST_LAMBDA_RETURN_EXPRESSION_NODE)) {
            this->analyzeLambdaReturnExpression((ASTLambdaReturnExpressionNode*)node, currentScope);
        } else if (node->is(AST_BLOCK_END_NODE)) {
            scopeStack.pop();
            if (_astTraverser.hasMore()) {
                currentScope = scopeStack.top();
            }
        }
        nextNode = _astTraverser.next();
    }
}
