//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-provider.h"
#include "type-type-signature-strategy/type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/primitive-type-type-signature-strategy/primitive-type-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-invocation-expression-type-signature-strategy/array-access-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-expression-type-signature-strategy/array-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/binary-expression-type-signature-strategy/binary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/concat-expression-type-signature-strategy/concat-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-method-invocation-expression-type-signature-strategy/class-method-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-property-expression-type-signature-strategy/class-property-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/curry-expression-type-signature-strategy/curry-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-invocation-expression-type-signature-strategy/function-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-return-expression-type-signature-strategy/function-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/identifier-expression-type-signature-strategy/identifier-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-expression-type-signature-strategy/lambda-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-with-fat-arrow-expression-type-signature-strategy/lambda-with-fat-arrow-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-return-expression-type-signature-strategy/lambda-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/literal-expression-type-signature-strategy/literal-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/new-class-instance-expression-type-signature-strategy/new-class-instance-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/object-access-expression-type-signature-strategy/object-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/object-access-invocation-expression-type-signature-strategy/object-access-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/struct-expression-type-signature-strategy/struct-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/this-expression-type-signature-strategy/this-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-access-expression-type-signature-strategy/tuple-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-access-invocation-expression-type-signature-strategy/tuple-access-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-expression-type-signature-strategy/tuple-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/unary-expression-type-signature-strategy/unary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/module-access-expression-type-signature-strategy/module-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/ref-expression-type-signature-strategy/ref-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/dref-expression-type-signature-strategy/dref-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/share-expression-type-signature-strategy/share-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/struct-type-type-signature-strategy/struct-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/ref-type-type-signature-strategy/ref-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/shared-type-type-signature-strategy/shared-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/module-type-type-signature-strategy/module-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/this-type-type-signature-strategy/this-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/lambda-type-type-signature-strategy/lambda-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/void-type-type-signature-strategy/void-type-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-key-value-type-signature-strategy/enum-key-value-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-type-signature-strategy.h"
#include "lambda-expression-scope-parameter-type-signature-strategy/lambda-expression-scope-parameter-type-signature-strategy.h"
#include "variable-type-signature-strategy/variable-type-signature-strategy.h"
#include "class-type-signature-strategy/class-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-type-signature-strategy/class-property-type-signature-strategy.h"
#include "class-type-signature-strategy/class-constructor-type-signature-strategy/class-constructor-type-signature-strategy.h"
#include "class-type-signature-strategy/class-method-type-signature-strategy/class-method-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-assignment-statement-type-signature-strategy/class-property-assignment-statement-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-shared-value-assignment-statement-type-signature-strategy/class-property-shared-value-assignment-statement-type-signature-strategy.h"
#include "class-type-signature-strategy/class-scope-parameter-type-signature-strategy/class-scope-parameter-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-item-type-signature-strategy/parameter-list-item-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-type-singature-strategy.h"
#include "function-type-signature-strategy/function-type-signature-strategy.h"
#include "procedure-type-signature-strategy/procedure-type-signature-strategy.h"
#include "literal-type-signature-strategy/literal-type-signature-strategy.h"
#include "access-modifier-type-signature-strategy/access-modifier-type-signature-strategy.h"
#include "variable-assignment-statement-type-signature-strategy/variable-assignment-statement-type-signature-strategy.h"
#include "shared-value-assignment-statement-type-signature-strategy/shared-value-assignment-statement-type-signature-strategy.h"
#include "array-access-assignment-statement-type-signature-strategy/array-access-assignment-statement-type-signature-strategy.h"
#include "array-access-shared-value-assignment-statement-type-signature-strategy/array-access-shared-value-assignment-statement-type-signature-strategy.h"
#include "object-access-assignment-statement-type-signature-strategy/object-access-assignment-statement-type-signature-strategy.h"
#include "object-access-shared-value-assignment-statement-type-signature-strategy/object-access-shared-value-assignment-statement-type-signature-strategy.h"
#include "tuple-access-assignment-statement-type-signature-strategy/tuple-access-assignment-statement-type-signature-strategy.h"
#include "tuple-access-shared-value-assignment-statement-type-signature-strategy/tuple-access-shared-value-assignment-statement-type-signature-strategy.h"
#include "module-access-assignment-statement-type-signature-strategy/module-access-assignment-statement-type-signature-strategy.h"
#include "module-access-shared-value-assignment-statement-type-signature-strategy/module-access-shared-value-assignment-statement-type-signature-strategy.h"
#include "block-type-signature-strategy/block-type-signature-strategy.h"
#include "if-statement-type-signature-strategy/if-statement-type-signature-strategy.h"
#include "try-statement-type-signature-strategy/try-statement-type-signature-strategy.h"
#include "while-statement-type-signature-strategy/while-statement-type-signature-strategy.h"
#include "for-in-statement-type-signature-strategy/for-in-statement-type-signature-strategy.h"
#include "condition-type-signature-strategy/condition-type-signature-strategy.h"
#include "expression-statement-type-signature-strategy/expression-statement-type-signature-strategy.h"
#include "import-type-signature-strategy/import-type-signature-strategy.h"
#include "module-type-signature-strategy/module-type-signature-strategy.h"
#include "interface-type-signature-strategy/interface-type-signature-strategy.h"
#include "interface-type-signature-strategy/interface-property-type-signature-strategy/interface-property-type-signature-strategy.h"
#include "custom-type-declaration-type-signature-strategy/custom-type-declaration-type-signature-strategy.h"
#include "argument-list-type-signature-strategy/argument-list-type-signature-strategy.h"
#include "../../type-signature-lookup-table/type-signature-lookup-table-factory.h"


TypeSignatureStrategyProvider::TypeSignatureStrategyProvider() {
    _typeSignatureStrategyMap = TypeSignatureStrategyMap();
    _literalTypeSignatureLookupTable = LiteralTypeSignatureLookupTable();
    _arrayPrototypeSignatureMap = ArrayPrototypeTypeSignatureMap();
    _stringPrototypeSignatureMap = StringPrototypeTypeSignatureMap();
    _refPrototypeSignatureMap = RefPrototypeTypeSignatureMap();
}

void TypeSignatureStrategyProvider::assignTypeSignatureFor(std::shared_ptr<ASTNode> node, std::shared_ptr<TypeSignatureContext> context, std::optional<std::shared_ptr<TypeSignatureLookupTable>> scope) {
    auto typeSignatureScope = scope.value_or(TypeSignatureLookupTableFactory::create());
    switch (node->getNodeType()) {
        case AST_MODULE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getModuleTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTModuleDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ENUM_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getEnumTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTEnumDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_VARIABLE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getVariableTypeSignatureStrategy()
                    ->assignAndAddToScope(std::dynamic_pointer_cast<ASTVariableDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getClassTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getClassPropertyTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassPropertyDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_CONSTRUCTOR_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getClassConstructorTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassConstructorDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_METHOD_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getClassMethodTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassMethodDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getClassPropertyAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassPropertyAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getClassPropertySharedValueAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassPropertySharedValueAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FUNCTION_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getFunctionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CUSTOM_TYPE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getCustomTypeDeclarationTypeSignatureStrategy()
                    ->assignAndAddToScope(std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_INTERFACE_TYPE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getInterfaceTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTInterfaceTypeDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_INTERFACE_PROPERTY_NODE:
            this->_typeSignatureStrategyMap
                    .getInterfacePropertyTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTInterfacePropertyNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_PROCEDURE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getProcedureTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        case AST_PRIMITIVE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getPrimitiveTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTPrimitiveTypeNode>(node), &_literalTypeSignatureLookupTable);
            break;
        case AST_CUSTOM_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getCustomTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTCustomTypeNode>(node), typeSignatureScope);
            break;
        case AST_ARRAY_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getArrayTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTArrayTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_STRUCT_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getStructTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTStructTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TUPLE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getTupleTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTupleTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_REF_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getRefTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTRefTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_SHARED_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getSharedTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTSharedTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_MODULE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getModuleTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTModuleTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_LAMBDA_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getLambdaTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLambdaTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_VOID_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getVoidTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTVoidTypeNode>(node), context, typeSignatureScope, this);
            break;
        case AST_THIS_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    .getThisTypeTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTThisTypeNode>(node), typeSignatureScope);
            break;
        case AST_BINARY_ARITHMETIC_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getBinaryExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTBinaryArithmeticExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_BINARY_COMPARATOR_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getBinaryExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTBinaryComparatorExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CONCAT_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getConcatExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTConcatExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getArrayAccessExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getArrayAccessInvocationExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTArrayAccessInvocationExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ARRAY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getArrayExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTArrayExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getClassMethodInvocationExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassMethodInvocationExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getClassPropertyAccessExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTClassPropertyAccessExpressionNode>(node), context, typeSignatureScope);
            break;
        case AST_CURRY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getCurryExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTCurryExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getFunctionInvocationExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFunctionInvocationExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FUNCTION_ARGUMENT_LIST_NODE:
            this->_typeSignatureStrategyMap
                    .getArgumentListTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getFunctionReturnExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_IDENTIFIER_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getIdentifierExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(node), context, typeSignatureScope);
            break;
        case AST_LAMBDA_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getLambdaExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLambdaExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getLambdaWithFatArrowExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLambdaWithFatArrowExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_LAMBDA_RETURN_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getLambdaReturnExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLambdaReturnExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_LITERAL_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getLiteralExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLiteralExpressionNode>(node), context, this);
            break;
        case AST_LOGICAL_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getLogicalExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLogicalExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getNewClassInstanceExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTNewClassInstanceExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_OBJECT_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getObjectAccessExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getObjectAccessInvocationExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTObjectAccessInvocationExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_STRUCT_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getStructExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTStructExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_THIS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getThisExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTThisExpressionNode>(node), typeSignatureScope);
            break;
        case AST_TUPLE_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getTupleAccessExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getTupleAccessInvocationExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTupleAccessInvocationExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TUPLE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getTupleExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTupleExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_UNARY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getUnaryExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTUnaryExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_MODULE_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getModuleAccessExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_SHARE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getShareExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTShareExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_REF_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getRefExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTRefExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_DREF_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    .getDrefExpressionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTDrefExpressionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_PUBLIC_NODE:
        case AST_PROTECTED_NODE:
        case AST_PRIVATE_NODE:
            this->_typeSignatureStrategyMap
                    .getAccessModifierTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTAccessModifierNode>(node));
            break;
        case AST_LITERAL_NODE:
        case AST_INT_LITERAL_NODE:
        case AST_FLOAT_LITERAL_NODE:
        case AST_CHAR_LITERAL_NODE:
        case AST_STRING_LITERAL_NODE:
        case AST_BOOLEAN_LITERAL_NODE:
            this->_typeSignatureStrategyMap
                    .getLiteralTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTLiteralNode>(node), &_literalTypeSignatureLookupTable);
            break;
        case AST_FUNCTION_PARAMETER_LIST_NODE:
            this->_typeSignatureStrategyMap
                    .getParameterListTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFunctionParameterListNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FUNCTION_PARAMETER_NODE:
            this->_typeSignatureStrategyMap
                    .getParameterListItemTypeSignatureStrategy()
                    ->assignAndAddToScope(std::dynamic_pointer_cast<ASTFunctionParameterNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ENUM_KEY_VALUE_NODE:
            this->_typeSignatureStrategyMap
                    .getEnumKeyValueTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTEnumKeyValueNode>(node), context, this);
            break;
        case AST_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    .getBlockTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTBlockNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CONTROL_FLOW_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    .getBlockTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTControlFlowBlockNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FUNCTION_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    .getBlockTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFunctionBlockNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TRY_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    .getBlockTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTryBlockNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CATCH_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    .getBlockTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTCatchBlockNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FINALLY_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    .getBlockTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTFinallyBlockNode>(node), context, typeSignatureScope, this);
            break;
        case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getVariableAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTVariableAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getSharedValueAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTSharedValueAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getArrayAccessAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTArrayAccessAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getArrayAccessSharedValueAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTArrayAccessSharedValueAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getObjectAccessAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTObjectAccessAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getObjectAccessSharedValueAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTObjectAccessSharedValueAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getTupleAccessAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTupleAccessAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getTupleAccessSharedValueAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTupleAccessSharedValueAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getModuleAccessAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTModuleAccessAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getModuleAccessSharedValueAssignmentStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTModuleAccessSharedValueAssignmentStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_EXPRESSION_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getExpressionStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTExpressionStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_CONTROL_FLOW_CONDITION_NODE:
            this->_typeSignatureStrategyMap
                    .getConditionTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTControlFlowConditionNode>(node), context, typeSignatureScope, this);
            break;
        case AST_FOR_IN_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getForStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTForInStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_WHILE_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getWhileStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTWhileStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_TRY_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getTryStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTTryStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_IF_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    .getIfStatementTypeSignatureStrategy()
                    ->assign(std::dynamic_pointer_cast<ASTIfStatementNode>(node), context, typeSignatureScope, this);
            break;
        case AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    .getImportTypeSignatureStrategy()
                    ->assignAndAddToScope(std::dynamic_pointer_cast<ASTImportSingleModuleDeclarationNode>(node), context, typeSignatureScope, this);
            break;
        default:
            throw std::logic_error("type signature strategy not setup for node: " + node->toString());
    }
}

void TypeSignatureStrategyProvider::assignInitialTypeSignatureFor(std::shared_ptr<ASTNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope) {
    switch (node->getNodeType()) {
        case AST_FUNCTION_DECLARATION_NODE:
            _typeSignatureStrategyMap.getFunctionTypeSignatureStrategy()->assignInitial(std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(node), context, scope, this);
            return;
        case AST_PROCEDURE_DECLARATION_NODE:
            _typeSignatureStrategyMap.getProcedureTypeSignatureStrategy()->assignInitial(std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node), context, scope, this);
            return;
        case AST_ENUM_DECLARATION_NODE:
            _typeSignatureStrategyMap.getEnumTypeSignatureStrategy()->assign(std::dynamic_pointer_cast<ASTEnumDeclarationNode>(node), context, scope, this);
            return;
        default:
            return;
    }
}

void TypeSignatureStrategyProvider::assignPostInitialTypeSignatureFor(std::shared_ptr<ASTNode> node, std::shared_ptr<TypeSignatureContext> context, std::optional<std::shared_ptr<TypeSignatureLookupTable>> scope) {
    auto typeSignatureScope = scope.value_or(TypeSignatureLookupTableFactory::create());
    switch (node->getNodeType()) {
        case AST_CLASS_DECLARATION_NODE:
            _typeSignatureStrategyMap.getClassTypeSignatureStrategy()->assignPostInitial(std::dynamic_pointer_cast<ASTClassDeclarationNode>(node), context, typeSignatureScope, this);
            return;
        default:
            return;
    }
}

std::shared_ptr<ParameterListItemTypeSignature> TypeSignatureStrategyProvider::generateLambdaExpressionScopeParameter(std::set<std::string>* capturedVariableIds) {
    return this->_typeSignatureStrategyMap.getLambdaExpressionScopeParameterTypeSignatureStrategy()->create(capturedVariableIds);
}

std::shared_ptr<ParameterListItemTypeSignature> TypeSignatureStrategyProvider::generateClassScopeParameter(std::shared_ptr<ClassTypeSignature> classTypeSignature) {
    return this->_typeSignatureStrategyMap.getClassScopeParameterTypeSignatureStrategy()->create(classTypeSignature);
}

std::optional<std::shared_ptr<FunctionTypeSignature>> TypeSignatureStrategyProvider::findArrayPrototypeTypeSignature(std::string id, std::shared_ptr<TypeSignature> elementType) {
    return _arrayPrototypeSignatureMap.find(id, elementType);
}

std::optional<std::shared_ptr<FunctionTypeSignature>> TypeSignatureStrategyProvider::findStringPrototypeTypeSignature(std::string id) {
    return _stringPrototypeSignatureMap.find(id);
}

std::optional<std::shared_ptr<FunctionTypeSignature>> TypeSignatureStrategyProvider::findRefPrototypeTypeSignature(std::string id, std::shared_ptr<TypeSignature> refType) {
    return _refPrototypeSignatureMap.find(id, refType);
}