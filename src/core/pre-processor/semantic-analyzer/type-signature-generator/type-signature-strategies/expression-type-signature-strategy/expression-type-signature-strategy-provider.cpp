//
// Created by Johny Georges on 2024-05-06.
//

#include "expression-type-signature-strategy-provider.h"

ExpressionTypeSignatureStrategyProvider::ExpressionTypeSignatureStrategyProvider(TypeSignatureLookupTable* typeSignatureLookupTable) {
    _expressionTypeSignatureStrategyMap = new ExpressionTypeSignatureStrategyMap();
    _typeSignatureLookupTable = typeSignatureLookupTable;
}

TypeSignature*  ExpressionTypeSignatureStrategyProvider::getTypeSignatureForExpression(ASTNode* node) {
    switch (node->getNodeType()) {
        case AST_BINARY_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                       ->getBinaryExpressionTypeSignatureStrategy()
                       ->create((ASTBinaryExpressionNode*)node, this);
        case AST_LOGICAL_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getLogicalExpressionTypeSignatureStrategy()
                    ->create((ASTLogicalExpressionNode*)node, this);
        case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                   ->getArrayAccessExpressionTypeSignatureStrategy()
                   ->create((ASTArrayAccessExpressionNode*)node, this);
        case AST_ARRAY_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getArrayExpressionTypeSignatureStrategy()
                    ->create((ASTArrayExpressionNode*)node, this);
        case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getClassMethodInvocationExpressionTypeSignatureStrategy()
                    ->create((ASTClassMethodInvocationExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getClassPropertyAccessExpressionTypeSignatureStrategy()
                    ->create((ASTClassPropertyAccessExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_CURRY_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getCurryExpressionTypeSignatureStrategy()
                    ->create((ASTCurryExpressionNode*)node, this);
        case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getFunctionInvocationExpressionTypeSignatureStrategy()
                    ->create((ASTFunctionInvocationExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getFunctionReturnExpressionTypeSignatureStrategy()
                    ->create((ASTFunctionReturnExpressionNode*)node, this);
        case AST_IDENTIFIER_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                    ->getIdentifierExpressionTypeSignatureStrategy()
                    ->create((ASTIdentifierExpressionNode*)node, this->_typeSignatureLookupTable);
        default:
            throw std::invalid_argument("unable to locate expression type signature strategy for given ast node type");
    }
}