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
#include "variable-assignment-statement-type-signature-strategy/variable-assignment-statement-type-signature-strategy.h"
#include "../../../../ast/ast-nodes/ast-scoped-block-node.h"

TypeSignatureStrategyProvider::TypeSignatureStrategyProvider() {
    _typeSignatureStrategyMap = new TypeSignatureStrategyMap();
    _literalTypeSignatureLookupTable = LiteralTypeSignatureLookupTable();
}

void TypeSignatureStrategyProvider::assignTypeSignatureForExpression(ASTExpressionNode* node, TypeSignatureLookupTable* scope) {

    switch (node->getNodeType()) {
        case AST_BINARY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getBinaryExpressionTypeSignatureStrategy()
                    ->assign((ASTBinaryExpressionNode*)node, scope, this);
            break;
        case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTArrayAccessExpressionNode*)node,scope, this);
            break;
        case AST_ARRAY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayExpressionTypeSignatureStrategy()
                    ->assign((ASTArrayExpressionNode*)node, scope, this);
            break;
        case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassMethodInvocationExpressionTypeSignatureStrategy()
                    ->assign((ASTClassMethodInvocationExpressionNode*)node, scope);
            break;
        case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassPropertyAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTClassPropertyAccessExpressionNode*)node, scope);
            break;
        case AST_CURRY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getCurryExpressionTypeSignatureStrategy()
                    ->assign((ASTCurryExpressionNode*)node, scope, this);
            break;
        case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getFunctionInvocationExpressionTypeSignatureStrategy()
                    ->assign((ASTFunctionInvocationExpressionNode*)node, scope);
            break;
        case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getFunctionReturnExpressionTypeSignatureStrategy()
                    ->assign((ASTFunctionReturnExpressionNode*)node, scope, this);
            break;
        case AST_IDENTIFIER_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getIdentifierExpressionTypeSignatureStrategy()
                    ->assign((ASTIdentifierExpressionNode*)node, scope);
            break;
        case AST_LAMBDA_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaExpressionTypeSignatureStrategy()
                    ->assign((ASTLambdaExpressionNode*)node, scope, this);
            break;
        case AST_LAMBDA_RETURN_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaReturnExpressionTypeSignatureStrategy()
                    ->assign((ASTLambdaReturnExpressionNode*)node, scope, this);
            break;
        case AST_LITERAL_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLiteralExpressionTypeSignatureStrategy()
                    ->assign((ASTLiteralExpressionNode*)node, this);
            break;
        case AST_LOGICAL_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLogicalExpressionTypeSignatureStrategy()
                    ->assign((ASTLogicalExpressionNode*)node, scope, this);
            break;
        case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getNewClassInstanceExpressionTypeSignatureStrategy()
                    ->assign((ASTNewClassInstanceExpressionNode*)node, scope);
            break;
        case AST_OBJECT_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getObjectAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTObjectAccessExpressionNode*)node, scope, this);
            break;
        case AST_STRUCT_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getStructExpressionTypeSignatureStrategy()
                    ->assign((ASTStructExpressionNode*)node, scope, this);
            break;
        case AST_THIS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getThisExpressionTypeSignatureStrategy()
                    ->assign((ASTThisExpressionNode*)node, scope);
            break;
        case AST_TUPLE_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTTupleAccessExpressionNode*)node, scope, this);
            break;
        case AST_TUPLE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleExpressionTypeSignatureStrategy()
                    ->assign((ASTTupleExpressionNode*)node, scope, this);
            break;
        case AST_UNARY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getUnaryExpressionTypeSignatureStrategy()
                    ->assign((ASTUnaryExpressionNode*)node, scope, this);
            break;
        default:
            throw std::logic_error("type signature strategy not setup for node: " + node->toString());
    }
}

void TypeSignatureStrategyProvider::assignTypeSignatureForType(ASTTypeNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getTypeTypeSignatureStrategy()
            ->assign(node, scope, this);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForBaseType(ASTTypeBaseNode* node, TypeSignatureLookupTable* scope) {
    switch (node->getNodeType()) {
        case AST_PRIMITIVE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getPrimitiveTypeTypeSignatureStrategy()
                    ->assign((ASTPrimitiveTypeNode*)node, &_literalTypeSignatureLookupTable);
            break;
        case AST_CUSTOM_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getCustomTypeTypeSignatureStrategy()
                    ->assign((ASTCustomTypeNode*)node, scope);
            break;
        case AST_ARRAY_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayTypeTypeSignatureStrategy()
                    ->assign((ASTArrayTypeNode*)node, scope, this);
            break;
        case AST_TUPLE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleTypeTypeSignatureStrategy()
                    ->assign((ASTTupleTypeNode*)node, scope, this);
            break;
        case AST_LAMBDA_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaTypeTypeSignatureStrategy()
                    ->assign((ASTLambdaTypeNode*)node, scope, this);
            break;
        case AST_THIS_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getThisTypeTypeSignatureStrategy()
                    ->assign((ASTThisTypeNode*)node, scope);
            break;
        default:
            throw std::logic_error("type signature strategy not setup for node: " + node->toString());
    }
}

void TypeSignatureStrategyProvider::assignTypeSignatureForClassProperty(ASTClassPropertyDeclarationNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getClassPropertyTypeSignatureStrategy()
            ->assign(node, scope, this);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForClassConstructor(ASTClassConstructorDeclarationNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getClassConstructorTypeSignatureStrategy()
            ->assign(node, scope, this);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForClassMethod(ASTClassMethodDeclarationNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getClassMethodTypeSignatureStrategy()
            ->assign(node, scope, this);
}


void TypeSignatureStrategyProvider::assignTypeSignatureForEnumKeyValue(ASTEnumKeyValueNode* node) {
    this->_typeSignatureStrategyMap
            ->getEnumKeyValueTypeSignatureStrategy()
            ->assign(node, this);
}


void TypeSignatureStrategyProvider::assignTypeSignatureForParameter(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getParameterListItemTypeSignatureStrategy()
            ->assign(node, scope, this);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForParameterList(ASTFunctionParameterListNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getParameterListTypeSignatureStrategy()
            ->assign(node, scope, this);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForLiteral(ASTLiteralNode* node) {
    this->_typeSignatureStrategyMap
            ->getLiteralTypeSignatureStrategy()
            ->assign(node, &_literalTypeSignatureLookupTable);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForAccessModifier(ASTAccessModifierNode* node) {
    this->_typeSignatureStrategyMap
            ->getAccessModifierTypeSignatureStrategy()
            ->assign(node);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope) {
    switch (node->getNodeType()) {
        case AST_ENUM_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getEnumTypeSignatureStrategy()
                    ->assign((ASTEnumDeclarationNode*)node, this);
            break;
        case AST_VARIABLE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getVariableTypeSignatureStrategy()
                    ->assign((ASTVariableDeclarationNode*)node, scope, this);
            break;
        case AST_CLASS_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassTypeSignatureStrategy()
                    ->assign((ASTClassDeclarationNode*)node, scope, this);
            break;
        case AST_CLASS_PROPERTY_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassPropertyTypeSignatureStrategy()
                    ->assign((ASTClassPropertyDeclarationNode*)node, scope, this);
            break;
        case AST_CLASS_CONSTRUCTOR_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassConstructorTypeSignatureStrategy()
                    ->assign((ASTClassConstructorDeclarationNode*)node, scope, this);
            break;
        case AST_CLASS_METHOD_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassMethodTypeSignatureStrategy()
                    ->assign((ASTClassMethodDeclarationNode*)node, scope, this);
            break;
        case AST_FUNCTION_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getFunctionTypeSignatureStrategy()
                    ->assign((ASTFunctionDeclarationNode*)node, scope, this);
            break;
        case AST_PROCEDURE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getProcedureTypeSignatureStrategy()
                    ->assign((ASTProcedureDeclarationNode*)node, scope, this);
            break;
        default:
            throw std::logic_error("type signature strategy not setup for node: " + node->toString());
    }
}

void TypeSignatureStrategyProvider::assignTypeSignatureForBlockContents(ASTScopedBlockNode* node, TypeSignatureLookupTable* scope) {
    this->_typeSignatureStrategyMap
            ->getBlockTypeSignatureStrategy()
            ->assign(node, scope, this);
}

void TypeSignatureStrategyProvider::assignTypeSignatureForStatement(ASTStatementNode* node, TypeSignatureLookupTable* scope) {

    switch (node->getNodeType()) {
        case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getVariableAssignmentStatementTypeSignatureStrategy()
                    ->assign((ASTVariableAssignmentStatementNode*)node, scope, this);
            break;
        default:
            throw std::logic_error("type signature strategy not setup for node: " + node->toString());
    }
}