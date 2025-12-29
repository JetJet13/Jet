//
// Created by Johny Georges on 2025-11-18.
//

#include "scope-analyzer.h"
#include "../../ast-traverser/ast-traverser.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"

void ScopeAnalyzer::traverse(ASTNode* startNode, ASTLookupTable* fileScope) {
    auto astTraverser = ASTTraverser();
    auto scope = new ASTLookupTable();
    scope->inherit(fileScope);
    auto scopeStack = std::stack<ASTLookupTable*>();
    scopeStack.push(scope);
    astTraverser.init(startNode);
    auto nextNode = astTraverser.next();
    auto currentScope = scopeStack.top();
    while (nextNode) {
        auto node = nextNode.value();
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            currentScope->insert(node->getId(), node);
        } else if (node->is(AST_FUNCTION_PARAMETER_NODE)) {
            auto parameterNode = (ASTFunctionParameterNode*)node;
            currentScope->insert(parameterNode->getIdentifier()->getId(), node);
        } else if (node->is(AST_CONTROL_FLOW_BLOCK_NODE)) {
            auto blockScope = new ASTLookupTable(currentScope);
            scopeStack.push(blockScope);
            currentScope = scopeStack.top();
        } else if (node->is(AST_REF_EXPRESSION_NODE)) {
            auto refExpression = (ASTRefExpressionNode*)node;
            if (refExpression->getExpressionNode()->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
                auto idExpression = (ASTIdentifierExpressionNode*)refExpression->getExpressionNode();
                auto referencedValue = currentScope->findAcrossScopes(idExpression->getId()).value();
                if (referencedValue->is(AST_VARIABLE_DECLARATION_NODE)) {
                    ((ASTVariableDeclarationNode*)referencedValue)->markAsReferenced();
                }

                if (referencedValue->is(AST_FUNCTION_PARAMETER_NODE)) {
                    ((ASTFunctionParameterNode*)referencedValue)->markAsReferenced();
                }
            } else {
                refExpression->getExpressionNode()->markAsReferenced();
            }
        } else if (node->is(AST_LAMBDA_EXPRESSION_NODE)) {
            auto lambdaScope = new ASTLookupTable(currentScope);
            lambdaScope->bindLambda((ASTLambdaExpressionNode *) node);
            scopeStack.push(lambdaScope);
            currentScope = scopeStack.top();
        } else if (node->is(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
            auto lambdaScope = new ASTLookupTable(currentScope);
            lambdaScope->bindLambdaFatArrow((ASTLambdaWithFatArrowExpressionNode *) node);
            scopeStack.push(lambdaScope);
            currentScope = scopeStack.top();
        } else if (currentScope->isLambdaScope() && node->isOneOf({ AST_IDENTIFIER_EXPRESSION_NODE, AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE })) {
            auto insideNode = currentScope->findWithin(node->getId());
            auto outsideNode = currentScope->findInOuterScope(node->getId());
            if (!insideNode && outsideNode.has_value() && outsideNode.value()->is(AST_VARIABLE_DECLARATION_NODE)) {
                auto capturedVariable = (ASTVariableDeclarationNode*)outsideNode.value();
                capturedVariable->markAsCaptured();
                currentScope->capture(capturedVariable);
            }
        } else if (node->isOneOf({ AST_BLOCK_END_NODE, AST_TERMINATOR_NODE })) {
            scopeStack.pop();
            if (!scopeStack.empty()) {
                currentScope = scopeStack.top();
            }
        }

        auto peekNode = astTraverser.peek();
        if (peekNode && peekNode.value()->is(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
            // we do this, so we can know when to pop the current scope
            // for lambda-with-fat-arrow-expression nodes
            // (since they don't have a block-end-node)
            astTraverser.insertTerminatorNodeAfterNext();
        }
        nextNode = astTraverser.next();
    }
}

void ScopeAnalyzer::process(ASTFileNode* fileNode) {
    auto fileScope = new ASTLookupTable();
    for (auto node : *fileNode->getBody()) {
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            auto globalVariable = (ASTDeclarationNode*)node;
            fileScope->insertGlobalVariable(node->getId(), globalVariable);
        } else if (node->isOneOf({ AST_FUNCTION_DECLARATION_NODE, AST_PROCEDURE_DECLARATION_NODE })) {
            this->traverse(node, fileScope);
        }
    }
}