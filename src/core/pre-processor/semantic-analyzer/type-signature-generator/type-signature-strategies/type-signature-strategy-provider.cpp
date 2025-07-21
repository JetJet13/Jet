//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-provider.h"
#include "type-type-signature-strategy/type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/primitive-type-type-signature-strategy/primitive-type-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
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
#include "expression-type-signature-strategies/sref-expression-type-signature-strategy/sref-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/struct-type-type-signature-strategy/struct-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/ref-type-type-signature-strategy/ref-type-type-signature-strategy.h"
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
#include "class-type-signature-strategy/class-scope-parameter-type-signature-strategy/class-scope-parameter-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-item-type-signature-strategy/parameter-list-item-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-type-singature-strategy.h"
#include "function-type-signature-strategy/function-type-signature-strategy.h"
#include "procedure-type-signature-strategy/procedure-type-signature-strategy.h"
#include "literal-type-signature-strategy/literal-type-signature-strategy.h"
#include "access-modifier-type-signature-strategy/access-modifier-type-signature-strategy.h"
#include "variable-assignment-statement-type-signature-strategy/variable-assignment-statement-type-signature-strategy.h"
#include "array-access-assignment-statement-type-signature-strategy/array-access-assignment-statement-type-signature-strategy.h"
#include "block-type-signature-strategy/block-type-signature-strategy.h"
#include "if-statement-type-signature-strategy/if-statement-type-signature-strategy.h"
#include "try-statement-type-signature-strategy/try-statement-type-signature-strategy.h"
#include "while-statement-type-signature-strategy/while-statement-type-signature-strategy.h"
#include "for-in-statement-type-signature-strategy/for-in-statement-type-signature-strategy.h"
#include "condition-type-signature-strategy/condition-type-signature-strategy.h"
#include "expression-statement-type-signature-strategy/expression-statement-type-signature-strategy.h"
#include "print-statement-type-signature-strategy/print-statement-type-signature-strategy.h"
#include "import-type-signature-strategy/import-type-signature-strategy.h"
#include "module-type-signature-strategy/module-type-signature-strategy.h"
#include "interface-type-signature-strategy/interface-type-signature-strategy.h"
#include "interface-type-signature-strategy/interface-property-type-signature-strategy/interface-property-type-signature-strategy.h"
#include "custom-type-declaration-type-signature-strategy/custom-type-declaration-type-signature-strategy.h"
#include "argument-list-type-signature-strategy/argument-list-type-signature-strategy.h"


TypeSignatureStrategyProvider::TypeSignatureStrategyProvider() {
    _typeSignatureStrategyMap = new TypeSignatureStrategyMap();
    _literalTypeSignatureLookupTable = LiteralTypeSignatureLookupTable();
    _arrayPrototypeSignatureMap = ArrayPrototypeTypeSignatureMap();
}

void TypeSignatureStrategyProvider::assignTypeSignatureFor(ASTNode* node, std::optional<TypeSignatureLookupTable*> scope) {
    auto typeSignatureScope = scope.value_or(new TypeSignatureLookupTable());
    switch (node->getNodeType()) {
        case AST_MODULE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getModuleTypeSignatureStrategy()
                    ->assign((ASTModuleDeclarationNode*) node, typeSignatureScope, this);
            break;
        case AST_ENUM_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getEnumTypeSignatureStrategy()
                    ->assign((ASTEnumDeclarationNode*) node, this);
            break;
        case AST_VARIABLE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getVariableTypeSignatureStrategy()
                    ->assignAndAddToScope((ASTVariableDeclarationNode *) node, typeSignatureScope, this);
            break;
        case AST_CLASS_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassTypeSignatureStrategy()
                    ->assign((ASTClassDeclarationNode *) node, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassPropertyTypeSignatureStrategy()
                    ->assign((ASTClassPropertyDeclarationNode *) node, typeSignatureScope, this);
            break;
        case AST_CLASS_CONSTRUCTOR_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassConstructorTypeSignatureStrategy()
                    ->assign((ASTClassConstructorDeclarationNode*) node, typeSignatureScope, this);
            break;
        case AST_CLASS_METHOD_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassMethodTypeSignatureStrategy()
                    ->assign((ASTClassMethodDeclarationNode*) node, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassPropertyAssignmentStatementTypeSignatureStrategy()
                    ->assign((ASTClassPropertyAssignmentStatementNode*) node, typeSignatureScope, this);
            break;
        case AST_FUNCTION_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getFunctionTypeSignatureStrategy()
                    ->assign((ASTFunctionDeclarationNode *) node, typeSignatureScope, this);
            break;
        case AST_CUSTOM_TYPE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getCustomTypeDeclarationTypeSignatureStrategy()
                    ->assignAndAddToScope((ASTCustomTypeDeclarationNode*)node, typeSignatureScope, this);
            break;
        case AST_INTERFACE_TYPE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getInterfaceTypeSignatureStrategy()
                    ->assign((ASTInterfaceTypeDeclarationNode*) node, typeSignatureScope, this);
            break;
        case AST_INTERFACE_PROPERTY_NODE:
            this->_typeSignatureStrategyMap
                    ->getInterfacePropertyTypeSignatureStrategy()
                    ->assign((ASTInterfacePropertyNode*) node, typeSignatureScope, this);
            break;
        case AST_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getTypeTypeSignatureStrategy()
                    ->assign((ASTTypeNode*)node, typeSignatureScope, this);
            break;
        case AST_PROCEDURE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getProcedureTypeSignatureStrategy()
                    ->assign((ASTProcedureDeclarationNode *) node, typeSignatureScope, this);
            break;
        case AST_PRIMITIVE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getPrimitiveTypeTypeSignatureStrategy()
                    ->assign((ASTPrimitiveTypeNode *) node, &_literalTypeSignatureLookupTable);
            break;
        case AST_CUSTOM_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getCustomTypeTypeSignatureStrategy()
                    ->assign((ASTCustomTypeNode *) node, typeSignatureScope);
            break;
        case AST_ARRAY_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayTypeTypeSignatureStrategy()
                    ->assign((ASTArrayTypeNode *) node, typeSignatureScope, this);
            break;
        case AST_STRUCT_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getStructTypeTypeSignatureStrategy()
                    ->assign((ASTStructTypeNode *) node, typeSignatureScope, this);
            break;
        case AST_TUPLE_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleTypeTypeSignatureStrategy()
                    ->assign((ASTTupleTypeNode *) node, typeSignatureScope, this);
            break;
        case AST_REF_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getRefTypeTypeSignatureStrategy()
                    ->assign((ASTRefTypeNode *) node, typeSignatureScope, this);
            break;
        case AST_LAMBDA_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaTypeTypeSignatureStrategy()
                    ->assign((ASTLambdaTypeNode*) node, typeSignatureScope, this);
            break;
        case AST_VOID_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getVoidTypeTypeSignatureStrategy()
                    ->assign((ASTVoidTypeNode*)node, typeSignatureScope, this);
            break;
        case AST_THIS_TYPE_NODE:
            this->_typeSignatureStrategyMap
                    ->getThisTypeTypeSignatureStrategy()
                    ->assign((ASTThisTypeNode*)node, typeSignatureScope);
            break;
        case AST_BINARY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getBinaryExpressionTypeSignatureStrategy()
                    ->assign((ASTBinaryExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_CONCAT_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getConcatExpressionTypeSignatureStrategy()
                    ->assign((ASTConcatExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTArrayAccessExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_ARRAY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayExpressionTypeSignatureStrategy()
                    ->assign((ASTArrayExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassMethodInvocationExpressionTypeSignatureStrategy()
                    ->assign((ASTClassMethodInvocationExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getClassPropertyAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTClassPropertyAccessExpressionNode *) node, typeSignatureScope);
            break;
        case AST_CURRY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getCurryExpressionTypeSignatureStrategy()
                    ->assign((ASTCurryExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getFunctionInvocationExpressionTypeSignatureStrategy()
                    ->assign((ASTFunctionInvocationExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_FUNCTION_ARGUMENT_LIST_NODE:
            this->_typeSignatureStrategyMap
                    ->getArgumentListTypeSignatureStrategy()
                    ->assign((ASTFunctionArgumentListNode*) node, typeSignatureScope, this);
            break;
        case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getFunctionReturnExpressionTypeSignatureStrategy()
                    ->assign((ASTFunctionReturnExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_IDENTIFIER_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getIdentifierExpressionTypeSignatureStrategy()
                    ->assign((ASTIdentifierExpressionNode *) node, typeSignatureScope);
            break;
        case AST_LAMBDA_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaExpressionTypeSignatureStrategy()
                    ->assign((ASTLambdaExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaWithFatArrowExpressionTypeSignatureStrategy()
                    ->assign((ASTLambdaWithFatArrowExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_LAMBDA_RETURN_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLambdaReturnExpressionTypeSignatureStrategy()
                    ->assign((ASTLambdaReturnExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_LITERAL_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLiteralExpressionTypeSignatureStrategy()
                    ->assign((ASTLiteralExpressionNode *) node, this);
            break;
        case AST_LOGICAL_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getLogicalExpressionTypeSignatureStrategy()
                    ->assign((ASTLogicalExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getNewClassInstanceExpressionTypeSignatureStrategy()
                    ->assign((ASTNewClassInstanceExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_OBJECT_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getObjectAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTObjectAccessExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getObjectAccessInvocationExpressionTypeSignatureStrategy()
                    ->assign((ASTObjectAccessInvocationExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_STRUCT_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getStructExpressionTypeSignatureStrategy()
                    ->assign((ASTStructExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_THIS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getThisExpressionTypeSignatureStrategy()
                    ->assign((ASTThisExpressionNode *) node, typeSignatureScope);
            break;
        case AST_TUPLE_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTTupleAccessExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleAccessInvocationExpressionTypeSignatureStrategy()
                    ->assign((ASTTupleAccessInvocationExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_TUPLE_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getTupleExpressionTypeSignatureStrategy()
                    ->assign((ASTTupleExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_UNARY_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getUnaryExpressionTypeSignatureStrategy()
                    ->assign((ASTUnaryExpressionNode *) node, typeSignatureScope, this);
            break;
        case AST_MODULE_ACCESS_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getModuleAccessExpressionTypeSignatureStrategy()
                    ->assign((ASTModuleAccessExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_REF_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getRefExpressionTypeSignatureStrategy()
                    ->assign((ASTRefExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_DREF_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getDrefExpressionTypeSignatureStrategy()
                    ->assign((ASTDrefExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_SREF_EXPRESSION_NODE:
            this->_typeSignatureStrategyMap
                    ->getSrefExpressionTypeSignatureStrategy()
                    ->assign((ASTSrefExpressionNode*) node, typeSignatureScope, this);
            break;
        case AST_PUBLIC_NODE:
        case AST_PROTECTED_NODE:
        case AST_PRIVATE_NODE:
            this->_typeSignatureStrategyMap
                    ->getAccessModifierTypeSignatureStrategy()
                    ->assign((ASTAccessModifierNode*)node);
            break;
        case AST_LITERAL_NODE:
        case AST_INT_LITERAL_NODE:
        case AST_FLOAT_LITERAL_NODE:
        case AST_CHAR_LITERAL_NODE:
        case AST_STRING_LITERAL_NODE:
        case AST_BOOLEAN_LITERAL_NODE:
            this->_typeSignatureStrategyMap
                    ->getLiteralTypeSignatureStrategy()
                    ->assign((ASTLiteralNode*)node, &_literalTypeSignatureLookupTable);
            break;
        case AST_FUNCTION_PARAMETER_LIST_NODE:
            this->_typeSignatureStrategyMap
                    ->getParameterListTypeSignatureStrategy()
                    ->assign((ASTFunctionParameterListNode*)node, typeSignatureScope, this);
            break;
        case AST_FUNCTION_PARAMETER_NODE:
            this->_typeSignatureStrategyMap
                    ->getParameterListItemTypeSignatureStrategy()
                    ->assignAndAddToScope((ASTFunctionParameterNode *) node, typeSignatureScope, this);
            break;
        case AST_ENUM_KEY_VALUE_NODE:
            this->_typeSignatureStrategyMap
                    ->getEnumKeyValueTypeSignatureStrategy()
                    ->assign((ASTEnumKeyValueNode*)node, this);
            break;
        case AST_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    ->getBlockTypeSignatureStrategy()
                    ->assign((ASTBlockNode*)node, typeSignatureScope, this);
            break;
        case AST_CONTROL_FLOW_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    ->getBlockTypeSignatureStrategy()
                    ->assign((ASTControlFlowBlockNode*)node, typeSignatureScope, this);
            break;
        case AST_FUNCTION_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    ->getBlockTypeSignatureStrategy()
                    ->assign((ASTFunctionBlockNode*)node, typeSignatureScope, this);
            break;
        case AST_TRY_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    ->getBlockTypeSignatureStrategy()
                    ->assign((ASTTryBlockNode*)node, typeSignatureScope, this);
            break;
        case AST_CATCH_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    ->getBlockTypeSignatureStrategy()
                    ->assign((ASTCatchBlockNode*)node, typeSignatureScope, this);
            break;
        case AST_FINALLY_BLOCK_NODE:
            this->_typeSignatureStrategyMap
                    ->getBlockTypeSignatureStrategy()
                    ->assign((ASTFinallyBlockNode*)node, typeSignatureScope, this);
            break;
        case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getVariableAssignmentStatementTypeSignatureStrategy()
                    ->assign((ASTVariableAssignmentStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getArrayAccessAssignmentStatementTypeSignatureStrategy()
                    ->assign((ASTArrayAccessAssignmentStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_EXPRESSION_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getExpressionStatementTypeSignatureStrategy()
                    ->assign((ASTExpressionStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_PRINT_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getPrintStatementTypeSignatureStrategy()
                    ->assign((ASTPrintStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_CONTROL_FLOW_CONDITION_NODE:
            this->_typeSignatureStrategyMap
                    ->getConditionTypeSignatureStrategy()
                    ->assign((ASTControlFlowConditionNode*)node, typeSignatureScope, this);
            break;
        case AST_FOR_IN_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getForStatementTypeSignatureStrategy()
                    ->assign((ASTForInStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_WHILE_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getWhileStatementTypeSignatureStrategy()
                    ->assign((ASTWhileStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_TRY_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getTryStatementTypeSignatureStrategy()
                    ->assign((ASTTryStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_IF_STATEMENT_NODE:
            this->_typeSignatureStrategyMap
                    ->getIfStatementTypeSignatureStrategy()
                    ->assign((ASTIfStatementNode*)node, typeSignatureScope, this);
            break;
        case AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE:
            this->_typeSignatureStrategyMap
                    ->getImportTypeSignatureStrategy()
                    ->assignAndAddToScope((ASTImportSingleModuleDeclarationNode*)node, typeSignatureScope, this);
            break;
        default:
            throw std::logic_error("type signature strategy not setup for node: " + node->toString());
    }
}

void TypeSignatureStrategyProvider::assignPartialTypeSignatureFor(ASTNode* node, std::optional<TypeSignatureLookupTable*> scope) {
    auto typeSignatureScope = scope.value_or(new TypeSignatureLookupTable());
    switch (node->getNodeType()) {
//        case AST_FUNCTION_DECLARATION_NODE:
//            return (new FunctionTypeSignature())->setId(node->getId());
//        case AST_PROCEDURE_DECLARATION_NODE:
//            return (new ProcedureTypeSignature())->setId(node->getId());
//        case AST_ENUM_DECLARATION_NODE:
//            return (new EnumTypeSignature())->setId(node->getId());
        case AST_CLASS_DECLARATION_NODE:
            _typeSignatureStrategyMap->getClassTypeSignatureStrategy()->assignPartial((ASTClassDeclarationNode*)node, typeSignatureScope, this);
//        case AST_MODULE_DECLARATION_NODE:
//            return (new ModuleTypeSignature())->setId(node->getId());
//            return (new UnknownTypeSignature())->setId(node->getId());
    }
}

ParameterListItemTypeSignature* TypeSignatureStrategyProvider::generateLambdaExpressionScopeParameter(TypeSignatureLookupTable* scope) {
    return this->_typeSignatureStrategyMap->getLambdaExpressionScopeParameterTypeSignatureStrategy()->create(scope);
}

ParameterListItemTypeSignature* TypeSignatureStrategyProvider::generateClassScopeParameter(ClassTypeSignature* classTypeSignature) {
    return this->_typeSignatureStrategyMap->getClassScopeParameterTypeSignatureStrategy()->create(classTypeSignature);
}

std::optional<FunctionTypeSignature*> TypeSignatureStrategyProvider::findArrayPrototypeTypeSignature(std::string id, TypeSignature* elementType) {
    return _arrayPrototypeSignatureMap.find(id, elementType);
}