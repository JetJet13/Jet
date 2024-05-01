//
// Created by Johny Georges on 2024-02-17.
//

#include "reducer-strategy.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"

ReducerStrategy::ReducerStrategy(TypeSignatureGenerator* typeSignatureGenerator) {
    _typeSignatureGenerator = typeSignatureGenerator;
}

ASTExpressionNode* ReducerStrategy::createExpressionNode(ASTNode* node) {

    if (node->is(AST_INT_LITERAL_NODE) ||
        node->is(AST_FLOAT_LITERAL_NODE) ||
        node->is(AST_STRING_LITERAL_NODE) ||
        node->is(AST_CHAR_LITERAL_NODE) ||
        node->is(AST_BOOLEAN_LITERAL_NODE)) {
        auto expression = new ASTLiteralExpressionNode((ASTLiteralNode*)node);
        return expression
        ->setTypeSignature(
            _typeSignatureGenerator->generateForLiteralExpression(expression)
        );
    } else if (node->is(AST_IDENTIFIER_NODE)) {
        auto expression = new ASTIdentifierExpressionNode((ASTIdentifierNode*)node);
        return expression
        ->setTypeSignature(
            _typeSignatureGenerator->generateForIdentifierExpression(expression)
        );
    } else if (node->is(AST_CLASS_PROPERTY_ACCESS_NODE)) {
        auto expression = new ASTClassPropertyAccessExpressionNode((ASTClassPropertyAccessNode*)node);
        return expression
        ->setTypeSignature(
            _typeSignatureGenerator->generateForClassPropertyAccessExpression(expression)
        );
    } else if (node->is(AST_THIS_NODE)) {
        auto expression = new ASTThisExpressionNode((ASTThisNode*)node);
        return expression
        ->setTypeSignature(
            _typeSignatureGenerator->generateForThisExpression(expression)
        );
    }

    return (ASTExpressionNode*)node;
}