//
// Created by Johny Georges on 2024-02-14.
//

#include "syntax-dfa.h"
#include "../../../dfa/dfa-node-factory.h"
#include "../../../dfa/dfa-transition-factory.h"

SyntaxDfa::SyntaxDfa() {
    _dfa = DFA();
    this->init();
}

DFA* SyntaxDfa::getDFA() {
    return &_dfa;
}

std::optional<std::shared_ptr<DFANode>> SyntaxDfa::findStartNode(std::optional<std::shared_ptr<ASTNode>> astNode) {
    if (astNode.has_value()) {
        return _dfa.findStartNode(astNode.value()->getNodeType());
    }
    return {};
}

void SyntaxDfa::init() {
    auto varDeclaration = DFANodeFactory::Once::create(AST_VARIABLE_DECLARATION_NODE);
    auto varInit = DFANodeFactory::Once::create(AST_VARIABLE_INIT_NODE);
    auto varType = DFANodeFactory::Once::create(AST_VARIABLE_TYPE_NODE);
    auto varDefinition = DFANodeFactory::Once::create(AST_VARIABLE_DEFINITION_NODE);
    auto identifier = DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE);
    auto identifierExpression = DFANodeFactory::Once::create(AST_IDENTIFIER_EXPRESSION_NODE);
    auto callableIdentifierExpression = DFANodeFactory::Once::create(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE);
    auto literalExpression = DFANodeFactory::Once::create(AST_LITERAL_EXPRESSION_NODE);
    auto arrayAccessExpression = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_EXPRESSION_NODE);
    auto arrayAccessInvocationExpression = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE);
    auto arrayExpression = DFANodeFactory::Once::create(AST_ARRAY_EXPRESSION_NODE);
    auto structExpression = DFANodeFactory::Once::create(AST_STRUCT_EXPRESSION_NODE);
    auto objectAccessExpression = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_EXPRESSION_NODE);
    auto objectAccessInvocationExpression = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE);
    auto binaryArithmeticExpression = DFANodeFactory::Once::create(AST_BINARY_ARITHMETIC_EXPRESSION_NODE);
    auto binaryComparatorExpression = DFANodeFactory::Once::create(AST_BINARY_COMPARATOR_EXPRESSION_NODE);
    auto logicalExpression = DFANodeFactory::Once::create(AST_LOGICAL_EXPRESSION_NODE);
    auto unaryExpression = DFANodeFactory::Once::create(AST_UNARY_EXPRESSION_NODE);
    auto binaryArithmeticOperator = DFANodeFactory::Once::create(AST_BINARY_ARITHMETIC_OPERATOR_NODE);
    auto binaryComparatorOperator = DFANodeFactory::Once::create(AST_BINARY_COMPARATOR_OPERATOR_NODE);
    auto logicalOperator = DFANodeFactory::Once::create(AST_LOGICAL_OPERATOR_NODE);
    auto unaryOperator = DFANodeFactory::Once::create(AST_UNARY_OPERATOR_NODE);
    auto arrayBase = DFANodeFactory::Once::create(AST_ARRAY_NODE);
    auto arrayAccess = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_NODE);
    auto arrayAccessAssignment = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_ASSIGNMENT_NODE);
    auto objectAccessAssignment = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_ASSIGNMENT_NODE);
    auto tupleAccessAssignment = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_ASSIGNMENT_NODE);
    auto moduleAccessAssignment = DFANodeFactory::Once::create(AST_MODULE_ACCESS_ASSIGNMENT_NODE);
    auto arrayAccessSharedValueAssignment = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE);
    auto objectAccessSharedValueAssignment = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE);
    auto tupleAccessSharedValueAssignment = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE);
    auto moduleAccessSharedValueAssignment = DFANodeFactory::Once::create(AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE);
    auto structKeyValue = DFANodeFactory::Once::create(AST_STRUCT_KEY_VALUE_NODE);
    auto block = DFANodeFactory::Once::create(AST_BLOCK_NODE);
    auto typeColon = DFANodeFactory::Once::create(AST_TYPE_COLON_NODE);
    auto structColon = DFANodeFactory::Once::create(AST_STRUCT_COLON_NODE);
    auto period = DFANodeFactory::Once::create(AST_PERIOD_NODE);
    auto drefKeyword = DFANodeFactory::Once::create(AST_DREF_NODE);
    auto drefExpression = DFANodeFactory::Once::create(AST_DREF_EXPRESSION_NODE);
    auto shareKeyword = DFANodeFactory::Once::create(AST_SHARE_NODE);
    auto sharedKeyword = DFANodeFactory::Once::create(AST_SHARED_NODE);
    auto shareExpression = DFANodeFactory::Once::create(AST_SHARE_EXPRESSION_NODE);
    auto functionDeclaration = DFANodeFactory::Once::create(AST_FUNCTION_DECLARATION_NODE);
    auto functionDefinition = DFANodeFactory::Once::create(AST_FUNCTION_DEFINITION_NODE);
    auto functionKeyword = DFANodeFactory::Once::create(AST_FUNCTION_NODE);
    auto functionName = DFANodeFactory::Once::create(AST_FUNCTION_NAME_NODE);
    auto functionCall = DFANodeFactory::Once::create(AST_FUNCTION_CALL_NODE);
    auto functionParameter = DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_NODE);
    auto functionParameterList = DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_NODE);
    auto functionArgument = DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_NODE);
    auto functionArgumentList = DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_LIST_NODE);
    auto functionReturn = DFANodeFactory::Once::create(AST_FUNCTION_RETURN_NODE);
    auto functionReturnExpression = DFANodeFactory::Once::create(AST_FUNCTION_RETURN_EXPRESSION_NODE);
    auto functionInvocationExpression = DFANodeFactory::Once::create(AST_FUNCTION_INVOCATION_EXPRESSION_NODE);
    auto procedureDeclaration = DFANodeFactory::Once::create(AST_PROCEDURE_DECLARATION_NODE);
    auto procedureDefinition = DFANodeFactory::Once::create(AST_PROCEDURE_DEFINITION_NODE);
    auto procedureKeyword = DFANodeFactory::Once::create(AST_PROCEDURE_NODE);
    auto type = DFANodeFactory::Once::create(AST_TYPE_NODE);
    auto varAssignment = DFANodeFactory::Once::create(AST_VARIABLE_ASSIGNMENT_NODE);
    auto sharedValueAssignment = DFANodeFactory::Once::create(AST_SHARED_VALUE_ASSIGNMENT_NODE);
    auto assignmentOperator = DFANodeFactory::Once::create(AST_ASSIGNMENT_OPERATOR_NODE);
    auto sharedValueAssignmentOperator = DFANodeFactory::Once::create(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE);
    auto varAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE);
    auto sharedValueAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE);
    auto arrayAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    auto objectAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    auto tupleAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    auto moduleAccessAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE, AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE);
    auto arrayAccessSharedValueAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE);
    auto objectAccessSharedValueAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE);
    auto tupleAccessSharedValueAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE);
    auto moduleAccessSharedValueAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE);
    auto enumDeclaration = DFANodeFactory::Once::createWithTarget(AST_ENUM_DECLARATION_NODE, AST_ENUM_DECLARATION_NODE);
    auto enumKeyword = DFANodeFactory::Once::create(AST_ENUM_NODE);
    auto enumName = DFANodeFactory::Once::create(AST_ENUM_NAME_NODE);
    auto enumKey = DFANodeFactory::Once::create(AST_ENUM_KEY_NODE);
    auto enumKeyValue = DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_NODE);
    auto enumKeyValueList = DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_LIST_NODE);
    auto tupleItem = DFANodeFactory::Once::create(AST_TUPLE_ITEM_NODE);
    auto tupleExpression = DFANodeFactory::Once::create(AST_TUPLE_EXPRESSION_NODE);
    auto tupleAccess = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_NODE);
    auto tupleAccessExpression = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_EXPRESSION_NODE);
    auto tupleAccessInvocationExpression = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE);
    auto objectAccessSource = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_SOURCE_NODE);
    auto objectAccessTarget = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_TARGET_NODE);
    auto ifKeyword = DFANodeFactory::Once::create(AST_IF_NODE);
    auto elseIfKeyword = DFANodeFactory::Once::create(AST_ELSE_IF_NODE);
    auto elseKeyword = DFANodeFactory::Once::create(AST_ELSE_NODE);
    auto ifBlock = DFANodeFactory::Once::create(AST_IF_BLOCK_NODE);
    auto elseIfBlock = DFANodeFactory::Once::create(AST_ELSE_IF_BLOCK_NODE);
    auto elseBlock = DFANodeFactory::Once::create(AST_ELSE_BLOCK_NODE);
    auto controlFlowCondition = DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE);
    auto controlFlowStatement = DFANodeFactory::Once::createWithTarget(AST_IF_STATEMENT_NODE, AST_IF_STATEMENT_NODE);
    auto controlFlowStart = DFANodeFactory::Once::createWithTarget(AST_IF_STATEMENT_NODE, AST_IF_STATEMENT_NODE);
    auto whileKeyword = DFANodeFactory::Once::create(AST_WHILE_NODE);
    auto whileStatement = DFANodeFactory::Once::createWithTarget(AST_WHILE_STATEMENT_NODE, AST_WHILE_STATEMENT_NODE);
    auto forKeyword = DFANodeFactory::Once::create(AST_FOR_NODE);
    auto forInKeyword = DFANodeFactory::Once::create(AST_FOR_IN_NODE);
    auto forSource = DFANodeFactory::Once::create(AST_FOR_IN_SOURCE_NODE);
    auto forVariable = DFANodeFactory::Once::create(AST_FOR_IN_VARIABLE_NODE);
    auto forStatement = DFANodeFactory::Once::createWithTarget(AST_FOR_IN_STATEMENT_NODE, AST_FOR_IN_STATEMENT_NODE);
    auto breakKeyword = DFANodeFactory::Once::createWithTarget(AST_BREAK_NODE, AST_BREAK_NODE);
    auto skipKeyword = DFANodeFactory::Once::createWithTarget(AST_SKIP_NODE, AST_SKIP_NODE);
    auto tryStatement = DFANodeFactory::Once::createWithTarget(AST_TRY_STATEMENT_NODE, AST_TRY_STATEMENT_NODE);
    auto tryKeyword = DFANodeFactory::Once::create(AST_TRY_NODE);
    auto catchKeyword = DFANodeFactory::Once::create(AST_CATCH_NODE);
    auto finallyKeyword = DFANodeFactory::Once::create(AST_FINALLY_NODE);
    auto catchErrorVariable = DFANodeFactory::Once::create(AST_CATCH_ERROR_VARIABLE_NODE);
    auto tryBlock = DFANodeFactory::Once::create(AST_TRY_BLOCK_NODE);
    auto catchBlock = DFANodeFactory::Once::create(AST_CATCH_BLOCK_NODE);
    auto finallyBlock = DFANodeFactory::Once::create(AST_FINALLY_BLOCK_NODE);
    auto fatArrowBase = DFANodeFactory::Once::create(AST_FAT_ARROW_BASE_NODE);
    auto lambdaTypeFatArrow = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_FAT_ARROW_NODE);
    auto lambdaExpressionFatArrow = DFANodeFactory::Once::create(AST_LAMBDA_EXPRESSION_FAT_ARROW_NODE);
    auto lambdaReturnExpression = DFANodeFactory::Once::create(AST_LAMBDA_RETURN_EXPRESSION_NODE);
    auto lambdaExpression = DFANodeFactory::Once::create(AST_LAMBDA_EXPRESSION_NODE);
    auto lambdaWithFatArrowExpression = DFANodeFactory::Once::create(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE);
    auto typeParameterList = DFANodeFactory::Once::create(AST_TYPE_PARAMETER_LIST_NODE);
    auto curryExpression = DFANodeFactory::Once::create(AST_CURRY_EXPRESSION_NODE);
    auto tupleType = DFANodeFactory::Once::createWithTarget(AST_TUPLE_TYPE_NODE, AST_TUPLE_TYPE_NODE);
    auto arrayType = DFANodeFactory::Once::createWithTarget(AST_ARRAY_TYPE_NODE, AST_ARRAY_TYPE_NODE);
    auto moduleKeyword = DFANodeFactory::Once::create(AST_MODULE_NODE);
    auto moduleSpread = DFANodeFactory::Once::create(AST_MODULE_SPREAD_NODE);
    auto moduleListNormalItem = DFANodeFactory::Once::create(AST_MODULE_LIST_NORMAL_ITEM_NODE);
    auto moduleListAliasItem = DFANodeFactory::Once::create(AST_MODULE_LIST_ALIAS_ITEM_NODE);
    auto moduleListSpreadItem = DFANodeFactory::Once::create(AST_MODULE_LIST_SPREAD_ITEM_NODE);
    auto asKeyword = DFANodeFactory::Once::create(AST_AS_NODE);
    auto importKeyword = DFANodeFactory::Once::create(AST_IMPORT_NODE);
    auto useKeyword = DFANodeFactory::Once::create(AST_USE_NODE);
    auto fromKeyword = DFANodeFactory::Once::create(AST_FROM_NODE);
    auto importModuleName = DFANodeFactory::Once::create(AST_IMPORT_MODULE_NAME_NODE);
    auto moduleAccess = DFANodeFactory::Once::create(AST_MODULE_ACCESS_NODE);
    auto moduleAccessType = DFANodeFactory::Once::create(AST_MODULE_ACCESS_TYPE_NODE);
    auto moduleTypeSource = DFANodeFactory::Once::create(AST_MODULE_TYPE_SOURCE_NODE);
    auto moduleTypeTarget = DFANodeFactory::Once::create(AST_MODULE_TYPE_TARGET_NODE);
    auto moduleAccessExpression = DFANodeFactory::Once::create(AST_MODULE_ACCESS_EXPRESSION_NODE);
    auto moduleAccessSource = DFANodeFactory::Once::create(AST_MODULE_ACCESS_SOURCE_NODE);
    auto moduleAccessTarget = DFANodeFactory::Once::create(AST_MODULE_ACCESS_TARGET_NODE);
    auto importModuleListByWildcardItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE);
    auto importModuleListByGroupItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE);
    auto importModuleListAliasItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE);
    auto importModuleListSpreadItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE);
    auto importModuleListNormalItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE);
    auto importModuleListWildcardItem = DFANodeFactory::Once::create(AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE);
    auto classKeyword = DFANodeFactory::Once::create(AST_CLASS_NODE);
    auto className = DFANodeFactory::Once::create(AST_CLASS_NAME_NODE);
    auto thisKeyword = DFANodeFactory::Once::create(AST_THIS_NODE);
    auto thisAccess = DFANodeFactory::Once::create(AST_THIS_ACCESS_NODE);
    auto thisExpression = DFANodeFactory::Once::create(AST_THIS_EXPRESSION_NODE);
    auto publicKeyword = DFANodeFactory::Once::create(AST_PUBLIC_NODE);
    auto protectedKeyword = DFANodeFactory::Once::create(AST_PROTECTED_NODE);
    auto privateKeyword = DFANodeFactory::Once::create(AST_PRIVATE_NODE);
    auto staticKeyword = DFANodeFactory::Once::create(AST_STATIC_NODE);
    auto constKeyword = DFANodeFactory::Once::create(AST_CONST_NODE);
    auto classMethodCall = DFANodeFactory::Once::create(AST_CLASS_METHOD_CALL_NODE);
    auto classMethodName = DFANodeFactory::Once::create(AST_CLASS_METHOD_NAME_NODE);
    auto classMethod = DFANodeFactory::Once::create(AST_CLASS_METHOD_DECLARATION_NODE);
    auto classPropertyName = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_NAME_NODE);
    auto classPropertyDefinition = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_DEFINITION_NODE);
    auto classPropertyDefinitionWithType = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE);
    auto classPropertyInit = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_INIT_NODE);
    auto classPropertyDeclaration = DFANodeFactory::Once::createWithTarget(AST_CLASS_PROPERTY_DECLARATION_NODE, AST_CLASS_PROPERTY_DECLARATION_NODE);
    auto classPropertyAccess = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_ACCESS_NODE);
    auto classPropertyAssignment = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_ASSIGNMENT_NODE);
    auto classPropertySharedValueAssignment = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_NODE);
    auto classMethodInvocationExpression = DFANodeFactory::Once::create(AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE);
    auto constructorKeyword = DFANodeFactory::Once::create(AST_CONSTRUCTOR_NODE);
    auto classConstructorDeclaration = DFANodeFactory::Once::createWithTarget(AST_CLASS_CONSTRUCTOR_DECLARATION_NODE, AST_CLASS_CONSTRUCTOR_DECLARATION_NODE);
    auto classAccess = DFANodeFactory::Once::create(AST_CLASS_ACCESS_NODE);
    auto newKeyword = DFANodeFactory::Once::create(AST_NEW_NODE);
    auto newClassInstance = DFANodeFactory::Once::create(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE);
    auto classMethodDefinition = DFANodeFactory::Once::create(AST_CLASS_METHOD_DEFINITION_NODE);
    auto classPropertyAccessExpression = DFANodeFactory::Once::create(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE);
    auto exportKeyword = DFANodeFactory::Once::create(AST_EXPORT_NODE);
    auto concatOperator = DFANodeFactory::Once::create(AST_CONCAT_NODE);
    auto concatExpression = DFANodeFactory::Once::create(AST_CONCAT_EXPRESSION_NODE);
    auto interfaceKeyword = DFANodeFactory::Once::create(AST_INTERFACE_NODE);
    auto interfaceName = DFANodeFactory::Once::create(AST_INTERFACE_NAME_NODE);
    auto interfaceDefinition = DFANodeFactory::Once::create(AST_INTERFACE_DEFINITION_NODE);
    auto interfacePropertyName = DFANodeFactory::Once::create(AST_INTERFACE_PROPERTY_NAME_NODE);
    auto interfaceProperty = DFANodeFactory::Once::create(AST_INTERFACE_PROPERTY_NODE);
    auto interfacePropertyList = DFANodeFactory::Once::create(AST_INTERFACE_PROPERTY_LIST_NODE);
    auto interfaceColon = DFANodeFactory::Once::create(AST_INTERFACE_COLON_NODE);
    auto structTypeKey = DFANodeFactory::Once::create(AST_STRUCT_TYPE_KEY_NODE);
    auto structTypeKeyValue = DFANodeFactory::Once::create(AST_STRUCT_TYPE_KEY_VALUE_NODE);
    auto structTypeColon = DFANodeFactory::Once::create(AST_STRUCT_TYPE_COLON_NODE);
    auto implementsKeyword = DFANodeFactory::Once::create(AST_IMPLEMENTS_NODE);
    auto implementsInterfaceName = DFANodeFactory::Once::create(AST_IMPLEMENTS_INTERFACE_NAME_NODE);
    auto implementsInterfaceNameLast = DFANodeFactory::Once::create(AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE);
    auto typeKeyword = DFANodeFactory::Once::create(AST_TYPE_KEYWORD_NODE);
    auto typeName = DFANodeFactory::Once::create(AST_TYPE_NAME_NODE);
    auto typeAssignmentOperator = DFANodeFactory::Once::create(AST_TYPE_ASSIGNMENT_OPERATOR_NODE);
    auto customTypeDeclaration = DFANodeFactory::Once::create(AST_CUSTOM_TYPE_DECLARATION_NODE);
    auto arrayTypeStart = DFANodeFactory::Once::create(AST_ARRAY_TYPE_START_NODE);
    auto arrayTypeEnd = DFANodeFactory::Once::create(AST_ARRAY_TYPE_END_NODE);
    auto lambdaTypeParameterListStart = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE);
    auto lambdaTypeParameterListEnd = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_PARAMETER_LIST_END_NODE);
    auto lambdaTypeParameterList = DFANodeFactory::Once::create(AST_LAMBDA_TYPE_PARAMETER_LIST_NODE);

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

    this->setupTransitionsWithTarget(classPropertySharedValueAssignment, AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, {
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
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_ARRAY_EXPRESSION_NODE,
            AST_STRUCT_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_CONCAT_EXPRESSION_NODE
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
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
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
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
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
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
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
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
    });

    identifier
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE, std::vector { AST_GROUP_START_NODE }));


    identifierExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
        AST_PERIOD_NODE
    })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_LOGICAL_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_TARGET_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_MODULE_ACCESS_SOURCE_NODE, std::vector { AST_MODULE_ACCESS_NODE, AST_MODULE_ACCESS_TYPE_NODE }))
    ->addReduceToTargetMapForPrevNode(std::make_shared<ReduceToTargetMap>(AST_MODULE_ACCESS_TARGET_NODE, std::vector { AST_MODULE_ACCESS_NODE, AST_MODULE_ACCESS_TYPE_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector { AST_FOR_IN_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_VARIABLE_NODE, std::vector { AST_FOR_NODE }, std::vector {AST_FOR_IN_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(typeColon))
    ->addTransition(DFATransitionFactory::create(structColon))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_SHARED_VALUE_ASSIGNMENT_NODE)));

    callableIdentifierExpression
    ->addReduceToTargetMapForPrevNode(std::make_shared<ReduceToTargetMap>(AST_MODULE_ACCESS_TARGET_NODE, std::vector { AST_MODULE_ACCESS_NODE }))
    ->addReduceToTargetMapForPrevNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_TARGET_NODE, std::vector { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE)));


    literalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
         AST_UNARY_OPERATOR_NODE
    })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_LOGICAL_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    arrayExpression
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_UNARY_OPERATOR_NODE })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector { AST_FOR_IN_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));

    arrayAccessExpression
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_ARRAY_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator))
    ->addTransition(DFATransitionFactory::create(period));

    structExpression
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator));

    tupleExpression
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator));

    objectAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_PERIOD_NODE,
    })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_OBJECT_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE)))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector { AST_FOR_IN_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector { AST_FOR_IN_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector { AST_FOR_IN_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector { AST_FOR_IN_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_MODULE_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE)))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_LOGICAL_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    binaryComparatorExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_LOGICAL_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
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
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator));


    unaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_LOGICAL_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator));

    classMethodInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    shareExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    drefExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryArithmeticOperator))
    ->addTransition(DFATransitionFactory::create(binaryComparatorOperator))
    ->addTransition(DFATransitionFactory::create(concatOperator));

    arrayBase
    ->addReduceToTargetMapForPrevNode(std::make_shared<ReduceToTargetMap>(AST_ARRAY_ACCESS_NODE, std::vector { AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_NODE, AST_ARRAY_EXPRESSION_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE, AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE, AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE, AST_MODULE_ACCESS_EXPRESSION_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_CURRY_EXPRESSION_NODE, AST_TUPLE_ACCESS_NODE, AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_FUNCTION_ARGUMENT_LIST_NODE }))
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
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
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
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_FUNCTION_RETURN_EXPRESSION_NODE, std::vector { AST_TERMINATOR_NODE }));

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
            AST_CONCAT_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE,
            AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
            AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE,
            AST_SHARE_EXPRESSION_NODE,
            AST_DREF_EXPRESSION_NODE,
            AST_THIS_EXPRESSION_NODE,
    });

    shareKeyword
    ->markAlwaysReduceSelf();

    this->setupTransitionsWithTarget(shareKeyword, AST_SHARE_EXPRESSION_NODE, {
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

    sharedKeyword
    ->reduceSelfWhenNextNodeIsOneOf({ AST_TYPE_PARAMETER_LIST_START_NODE })
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_TYPE_PARAMETER_LIST_NODE, AST_SHARED_TYPE_NODE)
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
            AST_SHARE_EXPRESSION_NODE,
    });

    functionReturnExpression
    ->markAlwaysReduceSelf();

    functionInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
    })
    ->markAlwaysReduceSelf()
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
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
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_ENUM_KEY_VALUE_NODE, std::vector { AST_COMMA_NODE, AST_ENUM_KEY_VALUE_LIST_END_NODE }))
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
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_CONTROL_FLOW_CONDITION_NODE, std::vector { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, std::vector { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(std::make_shared<ReduceToTargetDualMap>(AST_FOR_IN_SOURCE_NODE, std::vector {AST_FOR_IN_NODE }, std::vector {AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_TUPLE_ACCESS_ASSIGNMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE)))
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
            AST_SHARE_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(sharedValueAssignment, AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, {
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
            AST_DREF_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(arrayAccessSharedValueAssignment, AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, {
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
            AST_DREF_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(objectAccessSharedValueAssignment, AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, {
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
            AST_DREF_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(tupleAccessSharedValueAssignment, AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, {
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
            AST_DREF_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE
    });

    this->setupTransitionsWithTarget(moduleAccessSharedValueAssignment, AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE, {
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
            AST_DREF_EXPRESSION_NODE,
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

    sharedValueAssignmentOperator
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
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_SHARED_NODE });

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
            AST_SHARE_EXPRESSION_NODE,
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
            DFANodeFactory::Once::createWithTarget(AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE, AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_NODE)
    ))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::createAny(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)));

    classPropertyAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_UNARY_OPERATOR_NODE, AST_DREF_NODE, AST_SHARE_NODE })
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_ARITHMETIC_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_CONCAT_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_DREF_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_BINARY_COMPARATOR_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_SHARE_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addBacktrackToPredecessorRule(std::make_shared<BacktrackToPredecessorRule>(AST_BINARY_COMPARATOR_OPERATOR_NODE, AST_LOGICAL_OPERATOR_NODE))
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_OBJECT_ACCESS_SOURCE_NODE, std::vector { AST_PERIOD_NODE }))
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

    _dfa
    .insertStartNode(varDeclaration)
    ->insertStartNode(varType)
    ->insertStartNode(varDefinition)
    ->insertStartNode(varInit)
    ->insertStartNode(varAssignment)
    ->insertStartNode(sharedValueAssignment)
    ->insertStartNode(assignmentOperator)
    ->insertStartNode(sharedValueAssignmentOperator)
    ->insertStartNode(varAssignmentStatement)
    ->insertStartNode(sharedValueAssignmentStatement)
    ->insertStartNode(arrayAccessAssignmentStatement)
    ->insertStartNode(objectAccessAssignmentStatement)
    ->insertStartNode(tupleAccessAssignmentStatement)
    ->insertStartNode(moduleAccessAssignmentStatement)
    ->insertStartNode(arrayAccessSharedValueAssignmentStatement)
    ->insertStartNode(objectAccessSharedValueAssignmentStatement)
    ->insertStartNode(tupleAccessSharedValueAssignmentStatement)
    ->insertStartNode(moduleAccessSharedValueAssignmentStatement)
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
    ->insertStartNode(arrayAccessSharedValueAssignment)
    ->insertStartNode(objectAccessSharedValueAssignment)
    ->insertStartNode(tupleAccessSharedValueAssignment)
    ->insertStartNode(moduleAccessSharedValueAssignment)
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
    ->insertStartNode(classPropertySharedValueAssignment)
    ->insertStartNode(classMethodCall)
    ->insertStartNode(classMethodInvocationExpression)
    ->insertStartNode(constructorKeyword)
    ->insertStartNode(classConstructorDeclaration)
    ->insertStartNode(newKeyword)
    ->insertStartNode(newClassInstance)
    ->insertStartNode(classMethodDefinition)
    ->insertStartNode(classMethod)
    ->insertStartNode(exportKeyword)
    ->insertStartNode(drefKeyword)
    ->insertStartNode(drefExpression)
    ->insertStartNode(shareKeyword)
    ->insertStartNode(sharedKeyword)
    ->insertStartNode(shareExpression)
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
                            AST_SHARE_EXPRESSION_NODE,
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

void SyntaxDfa::setupTransitionsWithTarget(std::shared_ptr<DFANode> node, ASTNodeType targetNodeType, std::vector<ASTNodeType> nodeTypes) {
    for (auto nodeType : nodeTypes) {
        node->addTransition(
                DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(nodeType, targetNodeType)));
    }
}

void SyntaxDfa::initVarDefinition(std::shared_ptr<DFANode> varDefinition) {
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

void SyntaxDfa::initVarInit(std::shared_ptr<DFANode> varInitNode, ASTNodeType targetNodeType) {
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
                            DFANodeFactory::Once::createWithTarget(AST_SHARE_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_DREF_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_THIS_EXPRESSION_NODE, targetNodeType)))
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::createWithTarget(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, targetNodeType)));

}

void SyntaxDfa::initFunction(std::shared_ptr<DFANode> functionNode) {
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

void SyntaxDfa::initProcedure(std::shared_ptr<DFANode> procedureNode) {
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

void SyntaxDfa::initEnum(std::shared_ptr<DFANode> enumNode) {
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

void SyntaxDfa::initCustomType(std::shared_ptr<DFANode> typeKeyword) {
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

void SyntaxDfa::initIf(std::shared_ptr<DFANode> ifNode) {
    ifNode
        ->addTransition(DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE)
                ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_IF_BLOCK_NODE)
                ))
        ));
}

void SyntaxDfa::initElse(std::shared_ptr<DFANode> elseNode) {
    elseNode
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_ELSE_BLOCK_NODE)));
}

void SyntaxDfa::initElseIf(std::shared_ptr<DFANode> elseIfNode) {
    elseIfNode
        ->addTransition(DFATransitionFactory::create(
                DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE)
                ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_ELSE_IF_BLOCK_NODE)
                ))
        ));
}

void SyntaxDfa::initWhile(std::shared_ptr<DFANode> whileNode) {
    whileNode
            ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_CONTROL_FLOW_CONDITION_NODE)
                            ->addTransition(DFATransitionFactory::create(
                                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_WHILE_STATEMENT_NODE)
                            ))
            ));
}

void SyntaxDfa::initFor(std::shared_ptr<DFANode> forNode) {
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

void SyntaxDfa::initAccessModifier(std::shared_ptr<DFANode> accessModifier) {
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

void SyntaxDfa::initClassPropertyDefinition(std::shared_ptr<DFANode> classPropertyDefinition) {
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

void SyntaxDfa::initClassPropertyDefinitionWithType(std::shared_ptr<DFANode> classPropertyDefinitionWithType) {
    classPropertyDefinitionWithType
    ->addReduceToTargetMapForNextNode(std::make_shared<ReduceToTargetMap>(AST_CLASS_PROPERTY_INIT_NODE, std::vector { AST_TERMINATOR_NODE }))
    ->addTransition(
        DFATransitionFactory::create(
            DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_CLASS_PROPERTY_INIT_NODE)));
}