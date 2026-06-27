//
// Created by Johny Georges on 2024-02-14.
//

#include "syntax-dfa.h"
#include "../../../dfa/dfa-node-factory.h"
#include "../../../dfa/dfa-transition-factory.h"

SyntaxDfa::SyntaxDfa() {
    _dfa = new DFA();
    this->init();
}

DFA* SyntaxDfa::getDFA() {
    return _dfa;
}

std::optional<DFANode*> SyntaxDfa::findStartNode(std::optional<ASTNode*> astNode) {
    if (astNode.has_value()) {
        return _dfa->findStartNode(astNode.value()->getNodeType());
    }
    return {};
}

void SyntaxDfa::init() {
    DFANode* varDeclaration = DFANodeFactory::Once::create(AST_VARIABLE_DECLARATION_NODE);
    DFANode* varInit = DFANodeFactory::Once::create(AST_VARIABLE_INIT_NODE);
    DFANode* varType = DFANodeFactory::Once::create(AST_VARIABLE_TYPE_NODE);
    DFANode* varDefinition = DFANodeFactory::Once::create(AST_VARIABLE_DEFINITION_NODE);
    DFANode* identifier = DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE);
    DFANode* identifierExpression = DFANodeFactory::Once::create(AST_IDENTIFIER_EXPRESSION_NODE);
    DFANode* callableIdentifierExpression = DFANodeFactory::Once::create(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE);
    DFANode* literalExpression = DFANodeFactory::Once::create(AST_LITERAL_EXPRESSION_NODE);
    DFANode* arrayAccessExpression = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_EXPRESSION_NODE);
    DFANode* arrayAccessInvocationExpression = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE);
    DFANode* arrayExpression = DFANodeFactory::Once::create(AST_ARRAY_EXPRESSION_NODE);
    DFANode* structExpression = DFANodeFactory::Once::create(AST_STRUCT_EXPRESSION_NODE);
    DFANode* objectAccessExpression = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_EXPRESSION_NODE);
    DFANode* objectAccessInvocationExpression = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE);
    DFANode* binaryArithmeticExpression = DFANodeFactory::Once::create(AST_BINARY_ARITHMETIC_EXPRESSION_NODE);
    DFANode* binaryComparatorExpression = DFANodeFactory::Once::create(AST_BINARY_COMPARATOR_EXPRESSION_NODE);
    DFANode* logicalExpression = DFANodeFactory::Once::create(AST_LOGICAL_EXPRESSION_NODE);
    DFANode* unaryExpression = DFANodeFactory::Once::create(AST_UNARY_EXPRESSION_NODE);
    DFANode* binaryArithmeticOperator = DFANodeFactory::Once::create(AST_BINARY_ARITHMETIC_OPERATOR_NODE);
    DFANode* binaryComparatorOperator = DFANodeFactory::Once::create(AST_BINARY_COMPARATOR_OPERATOR_NODE);
    DFANode* logicalOperator = DFANodeFactory::Once::create(AST_LOGICAL_OPERATOR_NODE);
    DFANode* unaryOperator = DFANodeFactory::Once::create(AST_UNARY_OPERATOR_NODE);
    DFANode* arrayBase = DFANodeFactory::Once::create(AST_ARRAY_NODE);
    DFANode* arrayAccess = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_NODE);
    DFANode* arrayAccessAssignment = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_ASSIGNMENT_NODE);
    DFANode* objectAccessAssignment = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_ASSIGNMENT_NODE);
    DFANode* tupleAccessAssignment = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_ASSIGNMENT_NODE);
    DFANode* moduleAccessAssignment = DFANodeFactory::Once::create(AST_MODULE_ACCESS_ASSIGNMENT_NODE);
    DFANode* arrayAccessRefAssignment = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_REF_ASSIGNMENT_NODE);
    DFANode* objectAccessRefAssignment = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_REF_ASSIGNMENT_NODE);
    DFANode* tupleAccessRefAssignment = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_REF_ASSIGNMENT_NODE);
    DFANode* moduleAccessRefAssignment = DFANodeFactory::Once::create(AST_MODULE_ACCESS_REF_ASSIGNMENT_NODE);
    DFANode* structKeyValue = DFANodeFactory::Once::create(AST_STRUCT_KEY_VALUE_NODE);
    DFANode* block = DFANodeFactory::Once::create(AST_BLOCK_NODE);
    DFANode* typeColon = DFANodeFactory::Once::create(AST_TYPE_COLON_NODE);
    DFANode* structColon = DFANodeFactory::Once::create(AST_STRUCT_COLON_NODE);
    DFANode* period = DFANodeFactory::Once::create(AST_PERIOD_NODE);
    DFANode* refKeyword = DFANodeFactory::Once::create(AST_REF_NODE);
    DFANode* refTypeKeyword = DFANodeFactory::Once::create(AST_REF_TYPE_KEYWORD_NODE);
    DFANode* drefKeyword = DFANodeFactory::Once::create(AST_DREF_NODE);
    DFANode* srefKeyword = DFANodeFactory::Once::create(AST_SREF_NODE);
    DFANode* refExpression = DFANodeFactory::Once::create(AST_REF_EXPRESSION_NODE);
    DFANode* drefExpression = DFANodeFactory::Once::create(AST_DREF_EXPRESSION_NODE);
    DFANode* srefExpression = DFANodeFactory::Once::create(AST_SREF_EXPRESSION_NODE);
    DFANode* functionDeclaration = DFANodeFactory::Once::create(AST_FUNCTION_DECLARATION_NODE);
    DFANode* functionDefinition = DFANodeFactory::Once::create(AST_FUNCTION_DEFINITION_NODE);
    DFANode* functionKeyword = DFANodeFactory::Once::create(AST_FUNCTION_NODE);
    DFANode* functionName = DFANodeFactory::Once::create(AST_FUNCTION_NAME_NODE);
    DFANode* functionCall = DFANodeFactory::Once::create(AST_FUNCTION_CALL_NODE);
    DFANode* functionParameter = DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_NODE);
    DFANode* functionParameterList = DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_NODE);
    DFANode* functionArgument = DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_NODE);
    DFANode* functionArgumentList = DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_LIST_NODE);
    DFANode* functionReturn = DFANodeFactory::Once::create(AST_FUNCTION_RETURN_NODE);
    DFANode* functionReturnExpression = DFANodeFactory::Once::create(AST_FUNCTION_RETURN_EXPRESSION_NODE);
    DFANode* functionInvocationExpression = DFANodeFactory::Once::create(AST_FUNCTION_INVOCATION_EXPRESSION_NODE);
    DFANode* procedureDeclaration = DFANodeFactory::Once::create(AST_PROCEDURE_DECLARATION_NODE);
    DFANode* procedureDefinition = DFANodeFactory::Once::create(AST_PROCEDURE_DEFINITION_NODE);
    DFANode* procedureKeyword = DFANodeFactory::Once::create(AST_PROCEDURE_NODE);
    DFANode* type = DFANodeFactory::Once::create(AST_TYPE_NODE);
    DFANode* varAssignment = DFANodeFactory::Once::create(AST_VARIABLE_ASSIGNMENT_NODE);
    DFANode* refValueAssignment = DFANodeFactory::Once::create(AST_REF_VALUE_ASSIGNMENT_NODE);
    DFANode* assignmentOperator = DFANodeFactory::Once::create(AST_ASSIGNMENT_OPERATOR_NODE);
    DFANode* refValueAssignmentOperator = DFANodeFactory::Once::create(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE);
    DFANode* varAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE);
    DFANode* refValueAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE, AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE);
    DFANode* arrayAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    DFANode* objectAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    DFANode* tupleAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    DFANode* moduleAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    DFANode* arrayAccessRefAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE);
    DFANode* objectAccessRefAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE);
    DFANode* tupleAccessRefAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE);
    DFANode* moduleAccessRefAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, AST_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE);
    DFANode* enumDeclaration = DFANodeFactory::Once::createWithTarget(AST_ENUM_DECLARATION_NODE, AST_ENUM_DECLARATION_NODE);
    DFANode* enumKeyword = DFANodeFactory::Once::create(AST_ENUM_NODE);
    DFANode* enumName = DFANodeFactory::Once::create(AST_ENUM_NAME_NODE);
    DFANode* enumKey = DFANodeFactory::Once::create(AST_ENUM_KEY_NODE);
    DFANode* enumKeyValue = DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_NODE);
    DFANode* enumKeyValueList = DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_LIST_NODE);
    DFANode* tupleItem = DFANodeFactory::Once::create(AST_TUPLE_ITEM_NODE);
    DFANode* tupleExpression = DFANodeFactory::Once::create(AST_TUPLE_EXPRESSION_NODE);
    DFANode* tupleAccess = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_NODE);
    DFANode* tupleAccessExpression = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_EXPRESSION_NODE);
    DFANode* tupleAccessInvocationExpression = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE);
    DFANode* objectAccessSource = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_SOURCE_NODE);
    DFANode* objectAccessTarget = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_TARGET_NODE);
    DFANode* ifKeyword = DFANodeFactory::Once::create(AST_IF_NODE);
    DFANode* elseIfKeyword = DFANodeFactory::Once::create(AST_ELSE_IF_NODE);
    DFANode* elseKeyword = DFANodeFactory::Once::create(AST_ELSE_NODE);
    DFANode* ifBlock = DFANodeFactory::Once::create(AST_IF_BLOCK_NODE);
    DFANode* elseIfBlock = DFANodeFactory::Once::create(AST_ELSE_IF_BLOCK_NODE);
    DFANode* elseBlock = DFANodeFactory::Once::create(AST_ELSE_BLOCK_NODE);
    DFANode* controlFlowCondition = DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE);
    DFANode* controlFlowStatement = DFANodeFactory::Once::createWithTarget(AST_IF_STATEMENT_NODE, AST_IF_STATEMENT_NODE);
    DFANode* controlFlowStart = DFANodeFactory::Once::createWithTarget(AST_IF_STATEMENT_NODE, AST_IF_STATEMENT_NODE);
    DFANode* whileKeyword = DFANodeFactory::Once::create(AST_WHILE_NODE);
    DFANode* whileStatement = DFANodeFactory::Once::createWithTarget(AST_WHILE_STATEMENT_NODE, AST_WHILE_STATEMENT_NODE);
    DFANode* forKeyword = DFANodeFactory::Once::create(AST_FOR_NODE);
    DFANode* forInKeyword = DFANodeFactory::Once::create(AST_FOR_IN_NODE);
    DFANode* forSource = DFANodeFactory::Once::create(AST_FOR_IN_SOURCE_NODE);
    DFANode* forVariable = DFANodeFactory::Once::create(AST_FOR_IN_VARIABLE_NODE);
    DFANode* forStatement = DFANodeFactory::Once::createWithTarget(AST_FOR_IN_STATEMENT_NODE, AST_FOR_IN_STATEMENT_NODE);
    DFANode* breakKeyword = DFANodeFactory::Once::createWithTarget(AST_BREAK_NODE, AST_BREAK_NODE);
    DFANode* skipKeyword = DFANodeFactory::Once::createWithTarget(AST_SKIP_NODE, AST_SKIP_NODE);
    DFANode* tryStatement = DFANodeFactory::Once::createWithTarget(AST_TRY_STATEMENT_NODE, AST_TRY_STATEMENT_NODE);
    DFANode* tryKeyword = DFANodeFactory::Once::create(AST_TRY_NODE);
    DFANode* catchKeyword = DFANodeFactory::Once::create(AST_CATCH_NODE);
    DFANode* finallyKeyword = DFANodeFactory::Once::create(AST_FINALLY_NODE);
    DFANode* catchErrorVariable = DFANodeFactory::Once::create(AST_CATCH_ERROR_VARIABLE_NODE);
    DFANode* tryBlock = DFANodeFactory::Once::create(AST_TRY_BLOCK_NODE);
    DFANode* catchBlock = DFANodeFactory::Once::create(AST_CATCH_BLOCK_NODE);
    DFANode* finallyBlock = DFANodeFactory::Once::create(AST_FINALLY_BLOCK_NODE);
    DFANode* fatArrowBase = DFANodeFactory::Once::create(AST_FAT_ARROW_BASE_NODE);
    DFANode* lambdaTypeFatArrow = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_FAT_ARROW_NODE);
    DFANode* lambdaExpressionFatArrow = DFANodeFactory::Once::create(AST_LAMBDA_EXPRESSION_FAT_ARROW_NODE);
    DFANode* lambdaReturnExpression = DFANodeFactory::Once::create(AST_LAMBDA_RETURN_EXPRESSION_NODE);
    DFANode* lambdaExpression = DFANodeFactory::Once::create(AST_LAMBDA_EXPRESSION_NODE);
    DFANode* lambdaWithFatArrowExpression = DFANodeFactory::Once::create(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE);
    DFANode* typeParameterList = DFANodeFactory::Once::create(AST_TYPE_PARAMETER_LIST_NODE);
    DFANode* curryExpression = DFANodeFactory::Once::create(AST_CURRY_EXPRESSION_NODE);
    DFANode* tupleType = DFANodeFactory::Once::createWithTarget(AST_TUPLE_TYPE_NODE, AST_TUPLE_TYPE_NODE);
    DFANode* arrayType = DFANodeFactory::Once::createWithTarget(AST_ARRAY_TYPE_NODE, AST_ARRAY_TYPE_NODE);
    DFANode* moduleKeyword = DFANodeFactory::Once::create(AST_MODULE_NODE);
    DFANode* moduleSpread = DFANodeFactory::Once::create(AST_MODULE_SPREAD_NODE);
    DFANode* moduleListNormalItem = DFANodeFactory::Once::create(AST_MODULE_LIST_NORMAL_ITEM_NODE);
    DFANode* moduleListAliasItem = DFANodeFactory::Once::create(AST_MODULE_LIST_ALIAS_ITEM_NODE);
    DFANode* moduleListSpreadItem = DFANodeFactory::Once::create(AST_MODULE_LIST_SPREAD_ITEM_NODE);
    DFANode* asKeyword = DFANodeFactory::Once::create(AST_AS_NODE);
    DFANode* importKeyword = DFANodeFactory::Once::create(AST_IMPORT_NODE);
    DFANode* useKeyword = DFANodeFactory::Once::create(AST_USE_NODE);
    DFANode* fromKeyword = DFANodeFactory::Once::create(AST_FROM_NODE);
    DFANode* importModuleName = DFANodeFactory::Once::create(AST_IMPORT_MODULE_NAME_NODE);
    DFANode* moduleAccess = DFANodeFactory::Once::create(AST_MODULE_ACCESS_NODE);
    DFANode* moduleAccessType = DFANodeFactory::Once::create(AST_MODULE_ACCESS_TYPE_NODE);
    DFANode* moduleTypeSource = DFANodeFactory::Once::create(AST_MODULE_TYPE_SOURCE_NODE);
    DFANode* moduleTypeTarget = DFANodeFactory::Once::create(AST_MODULE_TYPE_TARGET_NODE);
    DFANode* moduleAccessExpression = DFANodeFactory::Once::create(AST_MODULE_ACCESS_EXPRESSION_NODE);
    DFANode* moduleAccessSource = DFANodeFactory::Once::create(AST_MODULE_ACCESS_SOURCE_NODE);
    DFANode* moduleAccessTarget = DFANodeFactory::Once::create(AST_MODULE_ACCESS_TARGET_NODE);
    DFANode* importModuleListByWildcardItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE);
    DFANode* importModuleListByGroupItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE);
    DFANode* importModuleListAliasItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE);
    DFANode* importModuleListSpreadItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE);
    DFANode* importModuleListNormalItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE);
    DFANode* importModuleListWildcardItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE);
    DFANode* classKeyword = DFANodeFactory::Once::create(AST_CLASS_NODE);
    DFANode* className = DFANodeFactory::Once::create(AST_CLASS_NAME_NODE);
    DFANode* thisKeyword = DFANodeFactory::Once::create(AST_THIS_NODE);
    DFANode* thisAccess = DFANodeFactory::Once::create(AST_THIS_ACCESS_NODE);
    DFANode* thisExpression = DFANodeFactory::Once::create(AST_THIS_EXPRESSION_NODE);
    DFANode* publicKeyword = DFANodeFactory::Once::create(AST_PUBLIC_NODE);
    DFANode* protectedKeyword = DFANodeFactory::Once::create(AST_PROTECTED_NODE);
    DFANode* privateKeyword = DFANodeFactory::Once::create(AST_PRIVATE_NODE);
    DFANode* staticKeyword = DFANodeFactory::Once::create(AST_STATIC_NODE);
    DFANode* constKeyword = DFANodeFactory::Once::create(AST_CONST_NODE);
    DFANode* classMethodCall = DFANodeFactory::Once::create(AST_CLASS_METHOD_CALL_NODE);
    DFANode* classMethodName = DFANodeFactory::Once::create(AST_CLASS_METHOD_NAME_NODE);
    DFANode* classMethod = DFANodeFactory::Once::create(AST_CLASS_METHOD_DECLARATION_NODE);
    DFANode* classPropertyName = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_NAME_NODE);
    DFANode* classPropertyDefinition = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_DEFINITION_NODE);
    DFANode* classPropertyDefinitionWithType = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE);
    DFANode* classPropertyInit = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_INIT_NODE);
    DFANode* classPropertyDeclaration = DFANodeFactory::Once::createWithTarget(AST_CLASS_PROPERTY_DECLARATION_NODE, AST_CLASS_PROPERTY_DECLARATION_NODE);
    DFANode* classPropertyAccess = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_ACCESS_NODE);
    DFANode* classPropertyAssignment = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_ASSIGNMENT_NODE);
    DFANode* classPropertyRefValueAssignment = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_NODE);
    DFANode* classMethodInvocationExpression = DFANodeFactory::Once::create(AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE);
    DFANode* constructorKeyword = DFANodeFactory::Once::create(AST_CONSTRUCTOR_NODE);
    DFANode* classConstructorDeclaration = DFANodeFactory::Once::createWithTarget(AST_CLASS_CONSTRUCTOR_DECLARATION_NODE, AST_CLASS_CONSTRUCTOR_DECLARATION_NODE);
    DFANode* classAccess = DFANodeFactory::Once::create(AST_CLASS_ACCESS_NODE);
    DFANode* newKeyword = DFANodeFactory::Once::create(AST_NEW_NODE);
    DFANode* newClassInstance = DFANodeFactory::Once::create(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE);
    DFANode* classMethodDefinition = DFANodeFactory::Once::create(AST_CLASS_METHOD_DEFINITION_NODE);
    DFANode* classPropertyAccessExpression = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE);
    DFANode* exportKeyword = DFANodeFactory::Once::create(AST_EXPORT_NODE);
    DFANode* concatOperator = DFANodeFactory::Once::create(AST_CONCAT_NODE);
    DFANode* concatExpression = DFANodeFactory::Once::create(AST_CONCAT_EXPRESSION_NODE);
    DFANode* interfaceKeyword = DFANodeFactory::Once::create(AST_INTERFACE_NODE);
    DFANode* interfaceName = DFANodeFactory::Once::create(AST_INTERFACE_NAME_NODE);
    DFANode* interfaceDefinition = DFANodeFactory::Once::create(AST_INTERFACE_DEFINITION_NODE);
    DFANode* interfacePropertyName = DFANodeFactory::Once::create(AST_INTERFACE_PROPERTY_NAME_NODE);
    DFANode* interfaceProperty = DFANodeFactory::Once::create(AST_INTERFACE_PROPERTY_NODE);
    DFANode* interfacePropertyList = DFANodeFactory::Once::create(AST_INTERFACE_PROPERTY_LIST_NODE);
    DFANode* interfaceColon = DFANodeFactory::Once::create(AST_INTERFACE_COLON_NODE);
    DFANode* structTypeKey = DFANodeFactory::Once::create(AST_STRUCT_TYPE_KEY_NODE);
    DFANode* structTypeKeyValue = DFANodeFactory::Once::create(AST_STRUCT_TYPE_KEY_VALUE_NODE);
    DFANode* structTypeColon = DFANodeFactory::Once::create(AST_STRUCT_TYPE_COLON_NODE);
    DFANode* implementsKeyword = DFANodeFactory::Once::create(AST_IMPLEMENTS_NODE);
    DFANode* implementsInterfaceName = DFANodeFactory::Once::create(AST_IMPLEMENTS_INTERFACE_NAME_NODE);
    DFANode* implementsInterfaceNameLast = DFANodeFactory::Once::create(AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE);
    DFANode* typeKeyword = DFANodeFactory::Once::create(AST_TYPE_KEYWORD_NODE);
    DFANode* typeName = DFANodeFactory::Once::create(AST_TYPE_NAME_NODE);
    DFANode* typeAssignmentOperator = DFANodeFactory::Once::create(AST_TYPE_ASSIGNMENT_OPERATOR_NODE);
    DFANode* customTypeDeclaration = DFANodeFactory::Once::create(AST_CUSTOM_TYPE_DECLARATION_NODE);
    DFANode* arrayTypeStart = DFANodeFactory::Once::create(AST_ARRAY_TYPE_START_NODE);
    DFANode* arrayTypeEnd = DFANodeFactory::Once::create(AST_ARRAY_TYPE_END_NODE);
    DFANode* lambdaTypeParameterListStart = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE);
    DFANode* lambdaTypeParameterListEnd = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_PARAMETER_LIST_END_NODE);
    DFANode* lambdaTypeParameterList = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_PARAMETER_LIST_NODE);
    DFANode* printKeyword = DFANodeFactory::Once::create(AST_PRINT_NODE);

//    todo: add support for arbitrary precision integers because the developer won't have to think about integer overflow.
//    todo: create built-in/first-class support for optional
//    todo: create built-in/first-class support for result
//    todo: add support for piping
//    todo: add support for traits
//    todo: add support for inheritance
//    todo: add support for tagged unions (sum types)
//    todo: add type-checker to prevent shadowing/re-declaring function parameters inside function blocks

    this->initVarDefinition(varDefinition);
    this->initVarInit(varInit, AST_VARIABLE_DECLARATION_NODE);
    this->initFunction(functionKeyword);
    this->initProcedure(procedureKeyword);
    this->initEnum(enumKeyword);
    this->initCustomType(typeKeyword);
    this->initIf(ifKeyword);
    this->initElse(elseKeyword);
    this->initElseIf(elseIfKeyword);
    this->initWhile(whileKeyword);
    this->initFor(forKeyword);
    this->initAccessModifier(publicKeyword);
    this->initAccessModifier(protectedKeyword);
    this->initAccessModifier(privateKeyword);
    this->initClassPropertyDefinition(classPropertyDefinition);
    this->initClassPropertyDefinitionWithType(classPropertyDefinitionWithType);
    this->initVarInit(classPropertyInit, AST_CLASS_PROPERTY_DECLARATION_NODE);
    this->initVarInit(classPropertyAssignment, AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE);

    this->setupTransitionsWithTarget(classPropertyRefValueAssignment, AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    varType
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_VARIABLE_DEFINITION_NODE)));

    this->setupTransitionsWithTarget(logicalOperator, AST_LOGICAL_EXPRESSION_NODE, {
            AST_IDENTIFIER_NODE,
            AST_EXPRESSION_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
    });

    this->setupTransitionsWithTarget(binaryArithmeticOperator, AST_BINARY_ARITHMETIC_EXPRESSION_NODE, {
            AST_IDENTIFIER_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(binaryComparatorOperator, AST_BINARY_COMPARATOR_EXPRESSION_NODE, {
            AST_IDENTIFIER_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    unaryOperator
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(unaryOperator, AST_UNARY_EXPRESSION_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
    });

    this->setupTransitionsWithTarget(concatOperator, AST_CONCAT_EXPRESSION_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_CONCAT_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
    });

    identifier
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE, { AST_GROUP_START_NODE }));


    identifierExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
        AST_PERIOD_NODE
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_TARGET_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_MODULE_ACCESS_SOURCE_NODE, { AST_MODULE_ACCESS_NODE, AST_MODULE_ACCESS_TYPE_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_MODULE_ACCESS_TARGET_NODE, { AST_MODULE_ACCESS_NODE, AST_MODULE_ACCESS_TYPE_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_VARIABLE_NODE, { AST_FOR_NODE }, {AST_FOR_IN_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(typeColon))
    ->addTransition(DFATransitionFactory::create(structColon))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_REF_VALUE_ASSIGNMENT_NODE)));

    callableIdentifierExpression
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_MODULE_ACCESS_TARGET_NODE, { AST_MODULE_ACCESS_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_TARGET_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE)));


    literalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
         AST_UNARY_OPERATOR_NODE
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    arrayExpression
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_UNARY_OPERATOR_NODE })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));

    arrayAccessExpression
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_ARRAY_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_ARRAY_ACCESS_REF_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    objectAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_PERIOD_NODE,
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_OBJECT_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_OBJECT_ACCESS_REF_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    arrayAccessInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE,
          AST_PERIOD_NODE,
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    objectAccessInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE,
          AST_PERIOD_NODE,
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    tupleAccessInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
        AST_PERIOD_NODE
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    moduleAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
        AST_NEW_NODE
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_MODULE_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_MODULE_ACCESS_REF_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    binaryArithmeticExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    binaryComparatorExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    concatExpression
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator));

    logicalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator));


    unaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator));

    classMethodInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    refExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    drefExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    srefExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    arrayBase
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_ARRAY_ACCESS_NODE, { AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_NODE, AST_ARRAY_EXPRESSION_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE, AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE, AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE, AST_MODULE_ACCESS_EXPRESSION_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_CURRY_EXPRESSION_NODE, AST_TUPLE_ACCESS_NODE, AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_FUNCTION_ARGUMENT_LIST_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_ARRAY_EXPRESSION_NODE)));

    arrayAccess
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_EXPRESSION_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE, AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE, AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE, AST_MODULE_ACCESS_EXPRESSION_NODE, AST_TUPLE_ACCESS_EXPRESSION_NODE });

    block
    ->markAlwaysReduceSelf();

    typeColon
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_DEFINITION_NODE, AST_CLASS_PROPERTY_DEFINITION_NODE, AST_FUNCTION_PARAMETER_LIST_NODE })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_FUNCTION_PARAMETER_NODE)));

    structColon
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_EXPRESSION_NODE })
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(structColon, AST_STRUCT_KEY_VALUE_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE
    });

    period
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_NODE, AST_TUPLE_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_TARGET_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE)));

    functionKeyword
    ->reduceSelfWhenNextNodeIsOneOf({ AST_FUNCTION_NAME_NODE });

    functionDefinition
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_FUNCTION_DECLARATION_NODE)
    ));

    functionName
    ->markAlwaysReduceSelf();

    functionParameter
    ->markAlwaysReduceSelf();

    functionParameterList
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_FUNCTION_NAME_NODE, AST_CLASS_METHOD_DEFINITION_NODE, AST_CONSTRUCTOR_NODE })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LAMBDA_RETURN_EXPRESSION_NODE, AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_LAMBDA_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(
        DFANodeFactory::Once::create(AST_TYPE_COLON_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_TYPE_NODE)
                        ->addTransition(
                            DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LAMBDA_RETURN_EXPRESSION_NODE, AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE))
                        )
                        ->addTransition(
                            DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_LAMBDA_EXPRESSION_NODE))
                        )
                )
            )
    ));

    functionArgument
    ->markAlwaysReduceSelf();

    functionArgumentList
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE, AST_CURRY_EXPRESSION_NODE })
    ->markAlwaysReduceSelf();


    functionReturn
    ->markAlwaysReduceSelf()
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_FUNCTION_RETURN_EXPRESSION_NODE, { AST_TERMINATOR_NODE }));

    this->setupTransitionsWithTarget(functionReturn, AST_FUNCTION_RETURN_EXPRESSION_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_SREF_EXPRESSION_NODE,
            AST_THIS_EXPRESSION_NODE,
    });


    refKeyword
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(refKeyword, AST_REF_EXPRESSION_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_THIS_EXPRESSION_NODE,
            AST_CONCAT_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE
    });

    refTypeKeyword
    ->reduceSelfWhenNextNodeIsOneOf({ AST_TYPE_PARAMETER_LIST_START_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_TYPE_PARAMETER_LIST_NODE, AST_REF_TYPE_NODE)
    ));

    drefKeyword
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(drefKeyword, AST_DREF_EXPRESSION_NODE, {
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_THIS_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE
    });

    srefKeyword
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(srefKeyword, AST_SREF_EXPRESSION_NODE, {
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_CURRY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_THIS_EXPRESSION_NODE,
    });


    functionReturnExpression
    ->markAlwaysReduceSelf();

    functionInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_CURRY_EXPRESSION_NODE)));

    curryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE,
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_CURRY_EXPRESSION_NODE)));

    procedureKeyword
    ->reduceSelfWhenNextNodeIsOneOf({ AST_FUNCTION_NAME_NODE });

    procedureDefinition
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_PROCEDURE_DECLARATION_NODE)
    ));

    enumKeyword
    ->markAlwaysReduceSelf();

    enumName
    ->markAlwaysReduceSelf();

    enumKey
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_ENUM_KEY_VALUE_NODE, { AST_COMMA_NODE, AST_ENUM_KEY_VALUE_LIST_END_NODE }))
    ->addTransition(DFATransitionFactory::create(
        DFANodeFactory::Once::create(AST_ASSIGNMENT_OPERATOR_NODE)
        ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_ENUM_KEY_VALUE_NODE)))
        ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_ENUM_KEY_VALUE_NODE)))
        ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_ENUM_KEY_VALUE_NODE)))
        ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_ENUM_KEY_VALUE_NODE)))
        ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_ENUM_KEY_VALUE_NODE)))
    ));


    enumKeyValue
    ->markAlwaysReduceSelf();

    enumKeyValueList
    ->markAlwaysReduceSelf();



    tupleItem
    ->markAlwaysReduceSelf();

    tupleAccess
    ->markAlwaysReduceSelf();

    tupleAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE,
    })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_IN_SOURCE_NODE, {AST_FOR_IN_NODE }, {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_TUPLE_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_TUPLE_ACCESS_REF_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    type
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(varAssignment, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(refValueAssignment, AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(arrayAccessRefAssignment, AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(objectAccessRefAssignment, AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(tupleAccessRefAssignment, AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(moduleAccessRefAssignment, AST_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(arrayAccessAssignment, AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(objectAccessAssignment, AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(moduleAccessAssignment, AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(tupleAccessAssignment, AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    assignmentOperator
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_DEFINITION_NODE, AST_CLASS_PROPERTY_DEFINITION_NODE, AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE, AST_CLASS_PROPERTY_ACCESS_NODE  })
    ->reduceSelfWhenNextNodeIsOneOf({ AST_TYPE_NODE });

    refValueAssignmentOperator
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_EXPRESSION_NODE, AST_CLASS_PROPERTY_ACCESS_NODE  });

    objectAccessSource
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_PERIOD_NODE })
    ->addTransition(DFATransitionFactory::create(period));

    objectAccessTarget
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_PERIOD_NODE });

    ifKeyword
    ->markAlwaysReduceSelf();

    elseKeyword
    ->reduceSelfWhenNextNodeIsOneOf({
            AST_BLOCK_START_NODE
    })
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_BLOCK_NODE })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IF_NODE, AST_ELSE_IF_NODE)));

    elseIfKeyword
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_BLOCK_NODE })
    ->markAlwaysReduceSelf();

    ifBlock
    ->reduceSelfWhenNextNodeIsOneOf({ AST_ELSE_NODE })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ELSE_BLOCK_NODE, AST_IF_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(
            DFANodeFactory::OnceOrMore::create(AST_ELSE_IF_BLOCK_NODE)
            ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ELSE_BLOCK_NODE, AST_IF_STATEMENT_NODE)))
            ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_IF_STATEMENT_NODE)))
    ))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_IF_STATEMENT_NODE)));

    elseIfBlock
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IF_BLOCK_NODE, AST_ELSE_IF_BLOCK_NODE });

    elseBlock
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IF_BLOCK_NODE, AST_ELSE_IF_BLOCK_NODE });

    controlFlowCondition
    ->markAlwaysReduceSelf()
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IF_BLOCK_NODE, AST_ELSE_IF_BLOCK_NODE, AST_WHILE_NODE });

    whileKeyword
    ->markAlwaysReduceSelf();

    forKeyword
    ->markAlwaysReduceSelf();

    forInKeyword
    ->markAlwaysReduceSelf();

    forVariable
    ->markAlwaysReduceSelf();

    forSource
    ->markAlwaysReduceSelf();

    tryKeyword
    ->reduceSelfWhenNextNodeIsOneOf({
        AST_BLOCK_START_NODE
    })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_TRY_BLOCK_NODE)));

    catchKeyword
    ->reduceSelfWhenNextNodeIsOneOf({
        AST_CATCH_ERROR_VARIABLE_NODE,
        AST_BLOCK_START_NODE
    })
    ->addTransition(DFATransitionFactory::create(
        DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_CATCH_BLOCK_NODE)
    ))
    ->addTransition(DFATransitionFactory::create(
        DFANodeFactory::Once::create(AST_CATCH_ERROR_VARIABLE_NODE)
            ->addTransition(DFATransitionFactory::create(
                DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_CATCH_BLOCK_NODE)
            ))
    ));

    finallyKeyword
    ->reduceSelfWhenNextNodeIsOneOf({
        AST_BLOCK_START_NODE
    })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_FINALLY_BLOCK_NODE)));

    catchErrorVariable
    ->markAlwaysReduceSelf()
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_CATCH_NODE });

    tryBlock
    ->reduceSelfWhenNextNodeIsOneOf({ AST_CATCH_NODE })
    ->addTransition(DFATransitionFactory::create(
        DFANodeFactory::Once::create(AST_CATCH_BLOCK_NODE)
            ->addTransition(DFATransitionFactory::create(
                DFANodeFactory::Once::createWithTarget(AST_FINALLY_BLOCK_NODE, AST_TRY_STATEMENT_NODE)
            ))
            ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_TRY_STATEMENT_NODE)))
    ));

    catchBlock
    ->reduceSelfWhenNextNodeIsOneOf({ AST_FINALLY_NODE })
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_TRY_BLOCK_NODE });

    finallyBlock
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_CATCH_BLOCK_NODE });

    fatArrowBase
    ->markAlwaysReduceSelf();

    lambdaReturnExpression
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE });

    lambdaExpression
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator));

    lambdaWithFatArrowExpression
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator));

    typeParameterList
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_REF_TYPE_KEYWORD_NODE });

    lambdaTypeFatArrow
    ->markAlwaysReduceSelf();

    lambdaExpressionFatArrow
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(lambdaExpressionFatArrow, AST_LAMBDA_RETURN_EXPRESSION_NODE, {
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_MODULE_ACCESS_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_LAMBDA_EXPRESSION_NODE,
            AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
            AST_LOGICAL_EXPRESSION_NODE,
            AST_UNARY_EXPRESSION_NODE,
            AST_CONCAT_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE,
            AST_REF_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE
    });

    arrayTypeStart
    ->markAlwaysReduceSelf()
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_TYPE_NODE)
            ->addTransition(
                    DFATransitionFactory::create(
                        DFANodeFactory::Once::createWithTarget(AST_ARRAY_TYPE_END_NODE, AST_ARRAY_TYPE_NODE))
            )
    ));

    arrayTypeEnd
    ->markAlwaysReduceSelf();

    lambdaTypeParameterListStart
    ->markAlwaysReduceSelf();

    lambdaTypeParameterListEnd
    ->markAlwaysReduceSelf();

    lambdaTypeParameterList
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_LAMBDA_TYPE_FAT_ARROW_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_LAMBDA_TYPE_NODE))
            )
    ));

    moduleKeyword
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_MODULE_NAME_NODE, AST_MODULE_DECLARATION_NODE)
    ));

    moduleSpread
    ->addTransition(DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_MODULE_NAME_NODE, AST_MODULE_LIST_SPREAD_ITEM_NODE)))
    ->addTransition(DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_IMPORT_MODULE_NAME_NODE, AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE)));

    moduleListNormalItem
    ->markAlwaysReduceSelf();

    moduleListAliasItem
    ->markAlwaysReduceSelf();

    moduleListSpreadItem
    ->markAlwaysReduceSelf();

    asKeyword
    ->markAlwaysReduceSelf();

    importKeyword
    ->markAlwaysReduceSelf()
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_IMPORT_MODULE_NAME_NODE)
                ->addTransition(
                    DFATransitionFactory::create(
                        DFANodeFactory::Once::create(AST_FROM_NODE)
                            ->addTransition(
                                DFATransitionFactory::create(
                                    DFANodeFactory::Once::createWithTarget(AST_IMPORT_PATH_NODE, AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE))
                            )
            ))
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_FROM_NODE)
                        ->addTransition(
                            DFATransitionFactory::create(
                                DFANodeFactory::Once::createWithTarget(AST_IMPORT_PATH_NODE, AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE))
                        )
            ))
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE)
                ->addTransition(
                    DFATransitionFactory::create(
                        DFANodeFactory::Once::create(AST_FROM_NODE)
                            ->addTransition(
                                DFATransitionFactory::create(
                                    DFANodeFactory::Once::createWithTarget(AST_IMPORT_PATH_NODE, AST_IMPORT_MANY_MODULE_DECLARATION_NODE))
                            )
                ))
    ));

    useKeyword
    ->markAlwaysReduceSelf()
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_IMPORT_MODULE_NAME_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_FROM_NODE)
                    ->addTransition(
                        DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_IMPORT_PATH_NODE, AST_USE_SINGLE_MODULE_DECLARATION_NODE))
                    )
            ))
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE)
            ->addTransition(
                 DFATransitionFactory::create(
                     DFANodeFactory::Once::create(AST_FROM_NODE)
                         ->addTransition(
                             DFATransitionFactory::create(
                                DFANodeFactory::Once::createWithTarget(AST_IMPORT_PATH_NODE, AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE))
                 )
            ))
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE)
                ->addTransition(
                    DFATransitionFactory::create(
                        DFANodeFactory::Once::create(AST_FROM_NODE)
                            ->addTransition(
                                DFATransitionFactory::create(
                                    DFANodeFactory::Once::createWithTarget(AST_IMPORT_PATH_NODE, AST_USE_MANY_MODULE_DECLARATION_NODE))
                            )
                ))
    ));

    importModuleName
    ->reduceSelfWhenNextNodeIsOneOf({ AST_FROM_NODE, AST_MODULE_ACCESS_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_AS_NODE)
                ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_IMPORT_MODULE_ALIAS_NAME_NODE, AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE)))
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_MODULE_ACCESS_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_IMPORT_WILDCARD_NODE, AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE)
                )
            )
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_IMPORT_MODULE_LIST_NODE, AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE)
                )
            )
    ));

    fromKeyword
    ->markAlwaysReduceSelf();

    moduleAccess
    ->markAlwaysReduceSelf();

    moduleAccessType
    ->markAlwaysReduceSelf();

    moduleTypeTarget
    ->markAlwaysReduceSelf();

    moduleTypeSource
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_MODULE_ACCESS_TYPE_NODE)
            ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_MODULE_TYPE_TARGET_NODE, AST_MODULE_TYPE_NODE))))
    );

    moduleAccessSource
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_MODULE_ACCESS_NODE)
            ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_MODULE_ACCESS_TARGET_NODE, AST_MODULE_ACCESS_EXPRESSION_NODE))))
    );

    importModuleListByWildcardItem
    ->markAlwaysReduceSelf();

    importModuleListByGroupItem
    ->markAlwaysReduceSelf();

    importModuleListAliasItem
    ->markAlwaysReduceSelf();

    importModuleListSpreadItem
    ->markAlwaysReduceSelf();

    importModuleListNormalItem
    ->markAlwaysReduceSelf();

    importModuleListWildcardItem
    ->markAlwaysReduceSelf();

    classKeyword
    ->markAlwaysReduceSelf()
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_CLASS_NAME_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::NilOrOnce::create(AST_IMPLEMENTS_INTERFACE_LIST_NODE)
                    ->addTransition(
                        DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_CLASS_BLOCK_NODE, AST_CLASS_DECLARATION_NODE)
                        )
                    )
            ))
        )
    );

    className
    ->markAlwaysReduceSelf();

    constructorKeyword
    ->reduceSelfWhenNextNodeIsOneOf({ AST_GROUP_START_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_NODE)
                ->addTransition(
                    DFATransitionFactory::create(
                        DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_CLASS_CONSTRUCTOR_DECLARATION_NODE)
                ))
    ));

    thisKeyword
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_THIS_ACCESS_NODE, AST_CLASS_ACCESS_NODE)
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::createAny(AST_THIS_EXPRESSION_NODE)
    ));

    classPropertyName
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_CLASS_ACCESS_NODE });

    classAccess
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_CLASS_PROPERTY_NAME_NODE, AST_CLASS_PROPERTY_ACCESS_NODE)
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_CLASS_METHOD_CALL_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)
            ))
    ));

    classPropertyAccess
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_CLASS_PROPERTY_ASSIGNMENT_NODE)
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_REF_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_NODE)
    ))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)));

    classPropertyAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_UNARY_OPERATOR_NODE, AST_DREF_NODE, AST_REF_NODE })
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_REF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(new BacktrackToPredecessorRule(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    classPropertyInit
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_CLASS_PROPERTY_DECLARATION_NODE)));

    classMethodCall
    ->markAlwaysReduceSelf();

    newKeyword
    ->markAlwaysReduceSelf()
    ->addTransition(
            // todo - add support for this: e.g. new Module::MyClass();
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_MODULE_ACCESS_EXPRESSION_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)
            ))
    ))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_CLASS_NAME_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)
            ))
    ));

    classMethodDefinition
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_CLASS_METHOD_DECLARATION_NODE)
                )
            )
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_TYPE_COLON_NODE)
                        ->addTransition(DFATransitionFactory::create(
                            DFANodeFactory::Once::create(AST_TYPE_NODE)
                                ->addTransition(
                                    DFATransitionFactory::create(
                                        DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_CLASS_METHOD_DECLARATION_NODE)
                                )
                            )
                        ))
                )
            )
        )
    );

    varInit
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE });

    exportKeyword
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(varInit))
    ->addTransition(DFATransitionFactory::create(functionDefinition))
    ->addTransition(DFATransitionFactory::create(procedureDefinition))
    ->addTransition(DFATransitionFactory::create(enumKeyword))
    ->addTransition(DFATransitionFactory::create(classKeyword))
    ->addTransition(DFATransitionFactory::create(typeKeyword))
    ->addTransition(DFATransitionFactory::create(interfaceDefinition));

    interfaceKeyword
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INTERFACE_NAME_NODE, AST_INTERFACE_DEFINITION_NODE)));

    interfaceDefinition
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INTERFACE_PROPERTY_LIST_NODE, AST_INTERFACE_TYPE_DECLARATION_NODE)));

    interfaceColon
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_INTERFACE_PROPERTY_NAME_NODE })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_INTERFACE_PROPERTY_NODE)));

    interfacePropertyName
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(interfaceColon));

    interfaceProperty
    ->markAlwaysReduceSelf();

    structTypeColon
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_STRUCT_TYPE_KEY_NODE })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_STRUCT_TYPE_KEY_VALUE_NODE)));

    structTypeKey
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(structTypeColon));

    structTypeKeyValue
    ->markAlwaysReduceSelf();

    implementsKeyword
    ->markAlwaysReduceSelf();

    implementsInterfaceName
    ->markAlwaysReduceSelf();

    typeKeyword
    ->markAlwaysReduceSelf();

    typeName
    ->markAlwaysReduceSelf();

    typeAssignmentOperator
    ->markAlwaysReduceSelf();

    printKeyword
    ->markAlwaysReduceSelf()
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_PRINT_STATEMENT_NODE)
    ));

    _dfa
    ->insertStartNode(varDeclaration)
    ->insertStartNode(varType)
    ->insertStartNode(varDefinition)
    ->insertStartNode(varInit)
    ->insertStartNode(varAssignment)
    ->insertStartNode(refValueAssignment)
    ->insertStartNode(assignmentOperator)
    ->insertStartNode(refValueAssignmentOperator)
    ->insertStartNode(varAssignmentStatement)
    ->insertStartNode(refValueAssignmentStatement)
    ->insertStartNode(arrayAccessAssignmentStatement)
    ->insertStartNode(objectAccessAssignmentStatement)
    ->insertStartNode(tupleAccessAssignmentStatement)
    ->insertStartNode(moduleAccessAssignmentStatement)
    ->insertStartNode(arrayAccessRefAssignmentStatement)
    ->insertStartNode(objectAccessRefAssignmentStatement)
    ->insertStartNode(tupleAccessRefAssignmentStatement)
    ->insertStartNode(moduleAccessRefAssignmentStatement)
    ->insertStartNode(identifier)
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(identifierExpression)
    ->insertStartNode(callableIdentifierExpression)
    ->insertStartNode(literalExpression)
    ->insertStartNode(structExpression)
    ->insertStartNode(objectAccessExpression)
    ->insertStartNode(objectAccessInvocationExpression)
    ->insertStartNode(moduleAccessExpression)
    ->insertStartNode(arrayExpression)
    ->insertStartNode(arrayAccessExpression)
    ->insertStartNode(arrayAccessInvocationExpression)
    ->insertStartNode(binaryArithmeticExpression)
    ->insertStartNode(binaryComparatorExpression)
    ->insertStartNode(logicalExpression)
    ->insertStartNode(unaryExpression)
    ->insertStartNode(functionInvocationExpression)
    ->insertStartNode(tupleExpression)
    ->insertStartNode(tupleAccessExpression)
    ->insertStartNode(tupleAccessInvocationExpression)
    ->insertStartNode(lambdaExpression)
    ->insertStartNode(lambdaWithFatArrowExpression)
    ->insertStartNode(concatExpression)
    ->insertStartNode(DFANodeFactory::Once::create(AST_GROUP_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_END_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_LEFT_BRACKET_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_STRUCT_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_TUPLE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_MODULE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_CONTROL_FLOW_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_TYPE_PARAMETER_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_CLASS_BLOCK_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_COLON_BASE_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_COMMA_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_PERIOD_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(typeColon)
    ->insertStartNode(structColon)
    ->insertStartNode(unaryOperator)
    ->insertStartNode(arrayBase)
    ->insertStartNode(arrayAccess)
    ->insertStartNode(arrayAccessAssignment)
    ->insertStartNode(objectAccessAssignment)
    ->insertStartNode(tupleAccessAssignment)
    ->insertStartNode(moduleAccessAssignment)
    ->insertStartNode(arrayAccessRefAssignment)
    ->insertStartNode(objectAccessRefAssignment)
    ->insertStartNode(tupleAccessRefAssignment)
    ->insertStartNode(moduleAccessRefAssignment)
    ->insertStartNode(structKeyValue)
    ->insertStartNode(block)
    ->insertStartNode(functionDeclaration)
    ->insertStartNode(functionDefinition)
    ->insertStartNode(functionKeyword)
    ->insertStartNode(functionName)
    ->insertStartNode(functionCall)
    ->insertStartNode(functionParameter)
    ->insertStartNode(functionParameterList)
    ->insertStartNode(functionArgument)
    ->insertStartNode(functionArgumentList)
    ->insertStartNode(functionReturn)
    ->insertStartNode(functionReturnExpression)
    ->insertStartNode(procedureDeclaration)
    ->insertStartNode(procedureDefinition)
    ->insertStartNode(procedureKeyword)
    ->insertStartNode(enumDeclaration)
    ->insertStartNode(enumKeyword)
    ->insertStartNode(enumName)
    ->insertStartNode(enumKey)
    ->insertStartNode(enumKeyValue)
    ->insertStartNode(enumKeyValueList)
    ->insertStartNode(tupleItem)
    ->insertStartNode(tupleAccess)
    ->insertStartNode(type)
    ->insertStartNode(objectAccessSource)
    ->insertStartNode(objectAccessTarget)
    ->insertStartNode(ifKeyword)
    ->insertStartNode(elseKeyword)
    ->insertStartNode(elseIfKeyword)
    ->insertStartNode(ifBlock)
    ->insertStartNode(elseIfBlock)
    ->insertStartNode(elseBlock)
    ->insertStartNode(controlFlowCondition)
    ->insertStartNode(controlFlowStatement)
    ->insertStartNode(whileKeyword)
    ->insertStartNode(whileStatement)
    ->insertStartNode(forKeyword)
    ->insertStartNode(forInKeyword)
    ->insertStartNode(forVariable)
    ->insertStartNode(forSource)
    ->insertStartNode(forStatement)
    ->insertStartNode(breakKeyword)
    ->insertStartNode(skipKeyword)
    ->insertStartNode(tryStatement)
    ->insertStartNode(tryKeyword)
    ->insertStartNode(catchKeyword)
    ->insertStartNode(finallyKeyword)
    ->insertStartNode(catchErrorVariable)
    ->insertStartNode(tryBlock)
    ->insertStartNode(catchBlock)
    ->insertStartNode(finallyBlock)
    ->insertStartNode(fatArrowBase)
    ->insertStartNode(lambdaReturnExpression)
    ->insertStartNode(typeParameterList)
    ->insertStartNode(lambdaTypeFatArrow)
    ->insertStartNode(lambdaExpressionFatArrow)
    ->insertStartNode(curryExpression)
    ->insertStartNode(tupleType)
    ->insertStartNode(arrayType)
    ->insertStartNode(moduleKeyword)
    ->insertStartNode(moduleSpread)
    ->insertStartNode(moduleListNormalItem)
    ->insertStartNode(moduleListAliasItem)
    ->insertStartNode(moduleListSpreadItem)
    ->insertStartNode(asKeyword)
    ->insertStartNode(importKeyword)
    ->insertStartNode(useKeyword)
    ->insertStartNode(importModuleName)
    ->insertStartNode(fromKeyword)
    ->insertStartNode(moduleAccess)
    ->insertStartNode(moduleAccessType)
    ->insertStartNode(moduleTypeSource)
    ->insertStartNode(moduleTypeTarget)
    ->insertStartNode(moduleAccessSource)
    ->insertStartNode(moduleAccessTarget)
    ->insertStartNode(importModuleListByWildcardItem)
    ->insertStartNode(importModuleListByGroupItem)
    ->insertStartNode(importModuleListAliasItem)
    ->insertStartNode(importModuleListSpreadItem)
    ->insertStartNode(importModuleListNormalItem)
    ->insertStartNode(importModuleListWildcardItem)
    ->insertStartNode(classKeyword)
    ->insertStartNode(className)
    ->insertStartNode(publicKeyword)
    ->insertStartNode(protectedKeyword)
    ->insertStartNode(privateKeyword)
    ->insertStartNode(staticKeyword)
    ->insertStartNode(constKeyword)
    ->insertStartNode(classPropertyName)
    ->insertStartNode(classPropertyDefinition)
    ->insertStartNode(classPropertyDefinitionWithType)
    ->insertStartNode(classPropertyInit)
    ->insertStartNode(classPropertyDeclaration)
    ->insertStartNode(classConstructorDeclaration)
    ->insertStartNode(thisKeyword)
    ->insertStartNode(thisExpression)
    ->insertStartNode(classAccess)
    ->insertStartNode(classPropertyAccess)
    ->insertStartNode(classPropertyAccessExpression)
    ->insertStartNode(classPropertyAssignment)
    ->insertStartNode(classPropertyRefValueAssignment)
    ->insertStartNode(classMethodCall)
    ->insertStartNode(classMethodInvocationExpression)
    ->insertStartNode(constructorKeyword)
    ->insertStartNode(classConstructorDeclaration)
    ->insertStartNode(newKeyword)
    ->insertStartNode(newClassInstance)
    ->insertStartNode(classMethodDefinition)
    ->insertStartNode(classMethod)
    ->insertStartNode(exportKeyword)
    ->insertStartNode(refKeyword)
    ->insertStartNode(refTypeKeyword)
    ->insertStartNode(drefKeyword)
    ->insertStartNode(srefKeyword)
    ->insertStartNode(refExpression)
    ->insertStartNode(drefExpression)
    ->insertStartNode(srefExpression)
    ->insertStartNode(interfaceKeyword)
    ->insertStartNode(interfaceName)
    ->insertStartNode(interfaceDefinition)
    ->insertStartNode(interfaceProperty)
    ->insertStartNode(interfacePropertyName)
    ->insertStartNode(interfaceColon)
    ->insertStartNode(interfacePropertyList)
    ->insertStartNode(structTypeColon)
    ->insertStartNode(structTypeKey)
    ->insertStartNode(structTypeKeyValue)
    ->insertStartNode(implementsKeyword)
    ->insertStartNode(implementsInterfaceName)
    ->insertStartNode(implementsInterfaceNameLast)
    ->insertStartNode(typeKeyword)
    ->insertStartNode(typeName)
    ->insertStartNode(typeAssignmentOperator)
    ->insertStartNode(customTypeDeclaration)
    ->insertStartNode(arrayTypeStart)
    ->insertStartNode(arrayTypeEnd)
    ->insertStartNode(lambdaTypeParameterListStart)
    ->insertStartNode(lambdaTypeParameterListEnd)
    ->insertStartNode(lambdaTypeParameterList)
    ->insertStartNode(printKeyword)
    ->insertStartNode(DFANodeFactory::Once::create(AST_IMPLEMENTS_INTERFACE_LIST_NODE))
    ->insertStartNode(DFANodeFactory::Once::create(AST_INTERFACE_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_INTERFACE_END_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_STRUCT_TYPE_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_STRUCT_TYPE_END_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_TUPLE_TYPE_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_TUPLE_TYPE_END_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BINARY_ARITHMETIC_OPERATOR_NODE)
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
                            AST_UNARY_EXPRESSION_NODE,
                            AST_LITERAL_EXPRESSION_NODE,
                            AST_IDENTIFIER_EXPRESSION_NODE
    }))
    ->insertStartNode(DFANodeFactory::Once::create(AST_BINARY_COMPARATOR_OPERATOR_NODE)
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
                            AST_UNARY_EXPRESSION_NODE,
                            AST_LITERAL_EXPRESSION_NODE,
                            AST_IDENTIFIER_EXPRESSION_NODE
                      }))
    ->insertStartNode(DFANodeFactory::Once::create(AST_CONCAT_NODE)
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                            AST_LITERAL_EXPRESSION_NODE,
                            AST_IDENTIFIER_EXPRESSION_NODE,
                            AST_REF_EXPRESSION_NODE,
                            AST_ARRAY_EXPRESSION_NODE,
                            AST_CONCAT_EXPRESSION_NODE
    }))
    ->insertStartNode(DFANodeFactory::Once::create(logicalOperator->getNodeType())
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
                            AST_BINARY_COMPARATOR_EXPRESSION_NODE,
                            AST_UNARY_EXPRESSION_NODE,
                            AST_LITERAL_EXPRESSION_NODE,
                            AST_IDENTIFIER_EXPRESSION_NODE
  }));
}

void SyntaxDfa::setupTransitionsWithTarget(DFANode* node, ASTNodeType targetNodeType, std::vector<ASTNodeType> nodeTypes) {
    for (auto nodeType : nodeTypes) {
        node->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(nodeType, targetNodeType)));
    }
}

void SyntaxDfa::initVarDefinition(DFANode* varDefinition) {
    varDefinition
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_TYPE_COLON_NODE)
            ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_TYPE_NODE)
                        ->addTransition(
                            DFATransitionFactory::create(
                                    DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_INIT_NODE)))
            ))
        )
    )
    ->addTransition(
            DFATransitionFactory::create(
                DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_INIT_NODE)));
}

void SyntaxDfa::initVarInit(DFANode* varInitNode, ASTNodeType targetNodeType) {
    varInitNode
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_TUPLE_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_MODULE_ACCESS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_LAMBDA_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_BINARY_ARITHMETIC_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_BINARY_COMPARATOR_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_CONCAT_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_REF_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_DREF_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_SREF_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_THIS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, targetNodeType)));

}

void SyntaxDfa::initFunction(DFANode* functionNode) {
    functionNode
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::create(AST_FUNCTION_NAME_NODE)
                                    ->addTransition(
                                            DFATransitionFactory::create(
                                                    DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_NODE)
                                                        ->addTransition(
                                                                DFATransitionFactory::create(
                                                                    DFANodeFactory::Once::create(AST_TYPE_COLON_NODE)
                                                                        ->addTransition(
                                                                                DFATransitionFactory::create(
                                                                                    DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_FUNCTION_DEFINITION_NODE)
                                                                        ))
                                                                )
                                                        ))
                                                    ))

            );
}

void SyntaxDfa::initProcedure(DFANode* procedureNode) {
    procedureNode
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::create(AST_FUNCTION_NAME_NODE)
                                    ->addTransition(
                                            DFATransitionFactory::create(
                                                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_PARAMETER_LIST_NODE, AST_PROCEDURE_DEFINITION_NODE)
                                            ))
                    )
            );
}

void SyntaxDfa::initEnum(DFANode* enumNode) {
    enumNode
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE })
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_ENUM_NAME_NODE)
                            ->addTransition(
                                    DFATransitionFactory::create(
                                            DFANodeFactory::Once::createWithTarget(AST_ENUM_KEY_VALUE_LIST_NODE, AST_ENUM_DECLARATION_NODE)
                                    ))
            )
    );
}

void SyntaxDfa::initCustomType(DFANode* typeKeyword) {
    typeKeyword
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_EXPORT_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_TYPE_NAME_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_TYPE_ASSIGNMENT_OPERATOR_NODE)
                    ->addTransition(
                        DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_CUSTOM_TYPE_DECLARATION_NODE)
                        )
                    )
                )
            )
        )
    );
}

void SyntaxDfa::initIf(DFANode* ifNode) {
    ifNode
        ->addTransition(DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE)
                ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_IF_BLOCK_NODE)
                ))
        ));
}

void SyntaxDfa::initElse(DFANode* elseNode) {
    elseNode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_ELSE_BLOCK_NODE)));
}

void SyntaxDfa::initElseIf(DFANode* elseIfNode) {
    elseIfNode
        ->addTransition(DFATransitionFactory::create(
                DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE)
                ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_ELSE_IF_BLOCK_NODE)
                ))
        ));
}

void SyntaxDfa::initWhile(DFANode* whileNode) {
    whileNode
            ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE)
                            ->addTransition(DFATransitionFactory::create(
                                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_WHILE_STATEMENT_NODE)
                            ))
            ));
}

void SyntaxDfa::initFor(DFANode* forNode) {
    forNode
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::create(AST_FOR_IN_VARIABLE_NODE)
                                    ->addTransition(
                                            DFATransitionFactory::create(
                                                    DFANodeFactory::Once::create(AST_FOR_IN_NODE)
                                                            ->addTransition(
                                                                    DFATransitionFactory::create(
                                                                            DFANodeFactory::Once::create(AST_FOR_IN_SOURCE_NODE)
                                                                                    ->addTransition(
                                                                                            DFATransitionFactory::create(
                                                                                                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_FOR_IN_STATEMENT_NODE)
                                                                                            ))
                                                                    ))
                                            ))
                    )
            );
}

void SyntaxDfa::initAccessModifier(DFANode* accessModifier) {
    accessModifier
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::NilOrOnce::create(AST_STATIC_NODE)
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CLASS_METHOD_NAME_NODE, AST_CLASS_METHOD_DEFINITION_NODE)
            ))
            ->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::NilOrOnce::create(AST_CONST_NODE)
                    ->addTransition(
                        DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_CLASS_PROPERTY_DEFINITION_NODE)
                    ))
            ))
        )
    );
}

void SyntaxDfa::initClassPropertyDefinition(DFANode* classPropertyDefinition) {
    classPropertyDefinition
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_TYPE_COLON_NODE)
            ->addTransition(DFATransitionFactory::create(
                DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE)
            ))
        )
    )
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_CLASS_PROPERTY_INIT_NODE)));
}

void SyntaxDfa::initClassPropertyDefinitionWithType(DFANode* classPropertyDefinitionWithType) {
    classPropertyDefinitionWithType
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_CLASS_PROPERTY_INIT_NODE, {AST_TERMINATOR_NODE }))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_CLASS_PROPERTY_INIT_NODE)));
}