//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-provider.h"

TypeSignatureStrategyProvider::TypeSignatureStrategyProvider(TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable) {
    _typeSignatureStrategyMap = new TypeSignatureStrategyMap();
    _typeSignatureLookupTable = typeSignatureLookupTable;
    _tokenTable = tokenTable;
}


TypeSignature*  TypeSignatureStrategyProvider::getTypeSignatureFor(ASTNode* node) {
    switch (node->getNodeType()) {
        case AST_BINARY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                       ->getBinaryExpressionTypeSignatureStrategy()
                       ->create((ASTBinaryExpressionNode*)node, this);
        case AST_LOGICAL_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLogicalExpressionTypeSignatureStrategy()
                    ->create((ASTLogicalExpressionNode*)node, this);
        case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                   ->getArrayAccessExpressionTypeSignatureStrategy()
                   ->create((ASTArrayAccessExpressionNode*)node, this);
        case AST_ARRAY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getArrayExpressionTypeSignatureStrategy()
                    ->create((ASTArrayExpressionNode*)node, this);
        case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassMethodInvocationExpressionTypeSignatureStrategy()
                    ->create((ASTClassMethodInvocationExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassPropertyAccessExpressionTypeSignatureStrategy()
                    ->create((ASTClassPropertyAccessExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_CURRY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getCurryExpressionTypeSignatureStrategy()
                    ->create((ASTCurryExpressionNode*)node, this);
        case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getFunctionInvocationExpressionTypeSignatureStrategy()
                    ->create((ASTFunctionInvocationExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getFunctionReturnExpressionTypeSignatureStrategy()
                    ->create((ASTFunctionReturnExpressionNode*)node, this);
        case AST_IDENTIFIER_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getIdentifierExpressionTypeSignatureStrategy()
                    ->create((ASTIdentifierExpressionNode*)node, this->_typeSignatureLookupTable);
        case AST_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getTypeTypeSignatureStrategy()
                    ->create((ASTTypeNode*)node, this);
        case AST_PRIMITIVE_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getPrimitiveTypeTypeSignatureStrategy()
                    ->create((ASTPrimitiveTypeNode*)node, this->_typeSignatureLookupTable);
        case AST_CUSTOM_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getCustomTypeTypeSignatureStrategy()
                    ->create((ASTCustomTypeNode*)node, this->_typeSignatureLookupTable, this->_tokenTable);
        case AST_ARRAY_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getArrayTypeTypeSignatureStrategy()
                    ->create((ASTArrayTypeNode*)node, this);
        case AST_INT_LITERAL_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getIntLiteralTypeTypeSignatureStrategy()
                    ->create((ASTIntLiteralTypeNode*)node, this->_tokenTable);
        default:
            throw std::invalid_argument("unable to locate expression type signature strategy for given ast node type");
    }
}