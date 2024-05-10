//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-provider.h"
#include "type-type-signature-strategy/type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/primitive-type-type-signature-strategy/primitive-type-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-expression-type-signature-strategy/array-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/binary-expression-type-signature-strategy/binary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-method-invocation-expression-type-signature-strategy/class-method-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-property-expression-type-signature-strategy/class-property-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/curry-expression-type-signature-strategy/curry-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-invocation-expression-type-signature-strategy/function-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-return-expression-type-signature-strategy/function-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/identifier-expression-type-signature-strategy/identifier-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-expression-type-signature-strategy/lambda-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/lambda-type-type-signature-strategy/lambda-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/this-type-type-signature-strategy/this-type-type-signature-strategy.h"

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
        case AST_TUPLE_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getTupleTypeTypeSignatureStrategy()
                    ->create((ASTTupleTypeNode*)node, this);
        case AST_LAMBDA_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLambdaTypeTypeSignatureStrategy()
                    ->create((ASTLambdaTypeNode*)node, this);
        case AST_THIS_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getThisTypeTypeSignatureStrategy()
                    ->create((ASTThisTypeNode*)node, this);
        default:
            throw std::invalid_argument("unable to locate expression type signature strategy for given ast node type");
    }
}