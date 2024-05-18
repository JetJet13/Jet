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
#include "expression-type-signature-strategies/lambda-return-expression-type-signature-strategy/lambda-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/literal-expression-type-signature-strategy/literal-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/new-class-instance-expression-type-signature-strategy/new-class-instance-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/object-access-expression-type-signature-strategy/object-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/struct-expression-type-signature-strategy/struct-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/this-expression-type-signature-strategy/this-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-access-expression-type-signature-strategy/tuple-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-expression-type-signature-strategy/tuple-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/unary-expression-type-signature-strategy/unary-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/lambda-type-type-signature-strategy/lambda-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/this-type-type-signature-strategy/this-type-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-key-value-type-signature-strategy/enum-key-value-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-type-signature-strategy.h"
#include "variable-type-signature-strategy/variable-type-signature-strategy.h"
#include "class-type-signature-strategy/class-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-type-signature-strategy/class-property-type-signature-strategy.h"
#include "class-type-signature-strategy/class-constructor-type-signature-strategy/class-constructor-type-signature-strategy.h"
#include "class-type-signature-strategy/class-method-type-signature-strategy/class-method-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-item-type-signature-strategy/parameter-list-item-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-type-singature-strategy.h"
#include "function-type-signature-strategy/function-type-signature-strategy.h"
#include "procedure-type-signature-strategy/procedure-type-signature-strategy.h"
#include "literal-type-signature-strategy/literal-type-signature-strategy.h"
#include "access-modifier-type-signature-strategy/access-modifier-type-signature-strategy.h"
#include "../../../../type-signature/unknown-type-signature/unknown-type-signature.h"

TypeSignatureStrategyProvider::TypeSignatureStrategyProvider(TokenTable* tokenTable) {
    _typeSignatureStrategyMap = new TypeSignatureStrategyMap();
    _literalTypeSignatureLookupTable = LiteralTypeSignatureLookupTable();
    _tokenTable = tokenTable;
}

TypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForExpression(ASTExpressionNode* node, TypeSignatureLookupTable* scope) {

    switch (node->getNodeType()) {
        case AST_BINARY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getBinaryExpressionTypeSignatureStrategy()
                    ->create((ASTBinaryExpressionNode*)node, scope, this);
        case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getArrayAccessExpressionTypeSignatureStrategy()
                    ->create((ASTArrayAccessExpressionNode*)node,scope, this);
        case AST_ARRAY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getArrayExpressionTypeSignatureStrategy()
                    ->create((ASTArrayExpressionNode*)node, scope, this);
        case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassMethodInvocationExpressionTypeSignatureStrategy()
                    ->create((ASTClassMethodInvocationExpressionNode*)node, scope);
        case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassPropertyAccessExpressionTypeSignatureStrategy()
                    ->create((ASTClassPropertyAccessExpressionNode*)node, scope);
        case AST_CURRY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getCurryExpressionTypeSignatureStrategy()
                    ->create((ASTCurryExpressionNode*)node, scope, this);
        case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getFunctionInvocationExpressionTypeSignatureStrategy()
                    ->create((ASTFunctionInvocationExpressionNode*)node, scope, this->_tokenTable);
        case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getFunctionReturnExpressionTypeSignatureStrategy()
                    ->create((ASTFunctionReturnExpressionNode*)node, scope, this);
        case AST_IDENTIFIER_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getIdentifierExpressionTypeSignatureStrategy()
                    ->create((ASTIdentifierExpressionNode*)node, scope, this->_tokenTable);
        case AST_LAMBDA_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLambdaExpressionTypeSignatureStrategy()
                    ->create((ASTLambdaExpressionNode*)node, scope, this);
        case AST_LAMBDA_RETURN_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLambdaReturnExpressionTypeSignatureStrategy()
                    ->create((ASTLambdaReturnExpressionNode*)node, scope, this);
        case AST_LITERAL_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLiteralExpressionTypeSignatureStrategy()
                    ->create((ASTLiteralExpressionNode*)node, this);
        case AST_LOGICAL_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLogicalExpressionTypeSignatureStrategy()
                    ->create((ASTLogicalExpressionNode*)node, scope, this);
        case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getNewClassInstanceExpressionTypeSignatureStrategy()
                    ->create((ASTNewClassInstanceExpressionNode*)node, scope, this->_tokenTable);
        case AST_OBJECT_ACCESS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getObjectAccessExpressionTypeSignatureStrategy()
                    ->create((ASTObjectAccessExpressionNode*)node, scope, this->_tokenTable, this);
        case AST_STRUCT_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getStructExpressionTypeSignatureStrategy()
                    ->create((ASTStructExpressionNode*)node, scope, this->_tokenTable, this);
        case AST_THIS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getThisExpressionTypeSignatureStrategy()
                    ->create((ASTThisExpressionNode*)node, scope);
        case AST_TUPLE_ACCESS_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getTupleAccessExpressionTypeSignatureStrategy()
                    ->create((ASTTupleAccessExpressionNode*)node, scope, this->_tokenTable, this);
        case AST_TUPLE_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getTupleExpressionTypeSignatureStrategy()
                    ->create((ASTTupleExpressionNode*)node, scope, this);
        case AST_UNARY_EXPRESSION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getUnaryExpressionTypeSignatureStrategy()
                    ->create((ASTUnaryExpressionNode*)node, scope, this);
        default:
            return new UnknownTypeSignature();
    }
}

TypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForType(ASTTypeNode* node, TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap
            ->getTypeTypeSignatureStrategy()
            ->create(node, scope, this);
}

TypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForBaseType(ASTTypeBaseNode* node, TypeSignatureLookupTable* scope) {
    switch (node->getNodeType()) {
        case AST_PRIMITIVE_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getPrimitiveTypeTypeSignatureStrategy()
                    ->create((ASTPrimitiveTypeNode*)node, &_literalTypeSignatureLookupTable);
        case AST_CUSTOM_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getCustomTypeTypeSignatureStrategy()
                    ->create((ASTCustomTypeNode*)node, scope, this->_tokenTable);
        case AST_ARRAY_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getArrayTypeTypeSignatureStrategy()
                    ->create((ASTArrayTypeNode*)node, scope, this);
        case AST_TUPLE_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getTupleTypeTypeSignatureStrategy()
                    ->create((ASTTupleTypeNode*)node, scope, this);
        case AST_LAMBDA_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getLambdaTypeTypeSignatureStrategy()
                    ->create((ASTLambdaTypeNode*)node, scope, this);
        case AST_THIS_TYPE_NODE:
            return this->_typeSignatureStrategyMap
                    ->getThisTypeTypeSignatureStrategy()
                    ->create((ASTThisTypeNode*)node, scope);
        default:
            return new UnknownTypeSignature();
    }
}

ClassPropertyTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForClassProperty(ASTClassPropertyDeclarationNode* node, TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap
            ->getClassPropertyTypeSignatureStrategy()
            ->create(node, scope, this);
}

ClassConstructorTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForClassConstructor(ASTClassConstructorDeclarationNode* node, TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap
            ->getClassConstructorTypeSignatureStrategy()
            ->create(node, scope, this);
}

ClassMethodTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForClassMethod(ASTClassMethodDeclarationNode* node, TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap
            ->getClassMethodTypeSignatureStrategy()
            ->create(node, scope, this);
}


LiteralTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForEnumKeyValue(ASTEnumKeyValueNode* node) {
    return this->_typeSignatureStrategyMap
            ->getEnumKeyValueTypeSignatureStrategy()
            ->create(node, this);
}


ParameterListItemTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForParameter(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap
            ->getParameterListItemTypeSignatureStrategy()
            ->create(node, scope, this->_tokenTable, this);
}

ParameterListTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForParameterList(ASTFunctionParameterListNode* node, TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap
            ->getParameterListTypeSignatureStrategy()
            ->create(node, scope, this);
}

LiteralTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForLiteral(ASTLiteralNode* node) {
    return this->_typeSignatureStrategyMap
            ->getLiteralTypeSignatureStrategy()
            ->create(node, &_literalTypeSignatureLookupTable);
}

AccessModifierTypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForAccessModifier(ASTAccessModifierNode* node) {
    return this->_typeSignatureStrategyMap
            ->getAccessModifierTypeSignatureStrategy()
            ->create(node);
}

TypeSignature* TypeSignatureStrategyProvider::getTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope) {
    switch (node->getNodeType()) {
        case AST_ENUM_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getEnumTypeSignatureStrategy()
                    ->create((ASTEnumDeclarationNode*)node, this->_tokenTable, this);
        case AST_VARIABLE_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getVariableTypeSignatureStrategy()
                    ->create((ASTVariableDeclarationNode*)node, scope, this);
        case AST_CLASS_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassTypeSignatureStrategy()
                    ->create((ASTClassDeclarationNode*)node, scope, this);
        case AST_CLASS_PROPERTY_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassPropertyTypeSignatureStrategy()
                    ->create((ASTClassPropertyDeclarationNode*)node, scope, this);
        case AST_CLASS_CONSTRUCTOR_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassConstructorTypeSignatureStrategy()
                    ->create((ASTClassConstructorDeclarationNode*)node, scope, this);
        case AST_CLASS_METHOD_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getClassMethodTypeSignatureStrategy()
                    ->create((ASTClassMethodDeclarationNode*)node, scope, this);
        case AST_FUNCTION_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getFunctionTypeSignatureStrategy()
                    ->create((ASTFunctionDeclarationNode*)node, scope, this);
        case AST_PROCEDURE_DECLARATION_NODE:
            return this->_typeSignatureStrategyMap
                    ->getProcedureTypeSignatureStrategy()
                    ->create((ASTProcedureDeclarationNode*)node, scope, this);
        default:
            return new UnknownTypeSignature();
    }
}