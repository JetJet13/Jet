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

    DFANode* varDeclaration = DFANodeFactory::Once::createWithTarget(AST_VARIABLE_DECLARATION_NODE, AST_VARIABLE_DECLARATION_NODE);
    DFANode* varInit = DFANodeFactory::Once::create(AST_VARIABLE_INIT_NODE);
    DFANode* varType = DFANodeFactory::Once::create(AST_VARIABLE_TYPE_NODE);
    DFANode* identifierExpression = DFANodeFactory::Once::create(AST_IDENTIFIER_EXPRESSION_NODE);
    DFANode* literalExpression = DFANodeFactory::Once::create(AST_LITERAL_EXPRESSION_NODE);
    DFANode* arrayAccessExpression = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_EXPRESSION_NODE);
    DFANode* arrayExpression = DFANodeFactory::Once::create(AST_ARRAY_EXPRESSION_NODE);
    DFANode* structExpression = DFANodeFactory::Once::create(AST_STRUCT_EXPRESSION_NODE);
    DFANode* objectAccessExpression = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_EXPRESSION_NODE);
    DFANode* binaryExpression = DFANodeFactory::Once::create(AST_BINARY_EXPRESSION_NODE);
    DFANode* logicalExpression = DFANodeFactory::Once::create(AST_LOGICAL_EXPRESSION_NODE);
    DFANode* unaryExpression = DFANodeFactory::Once::create(AST_UNARY_EXPRESSION_NODE);
    DFANode* binaryOperator = DFANodeFactory::Once::create(AST_BINARY_OPERATOR_NODE);
    DFANode* logicalOperator = DFANodeFactory::Once::create(AST_LOGICAL_OPERATOR_NODE);
    DFANode* unaryOperator = DFANodeFactory::Once::create(AST_UNARY_OPERATOR_NODE);
    DFANode* arrayBase = DFANodeFactory::Once::create(AST_ARRAY_NODE);
    DFANode* arrayAccess = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_NODE);
    DFANode* structKeyValue = DFANodeFactory::Once::create(AST_STRUCT_KEY_VALUE_NODE);
    DFANode* block = DFANodeFactory::Once::create(AST_BLOCK_NODE);
    DFANode* colon = DFANodeFactory::Once::create(AST_COLON_NODE);
    DFANode* period = DFANodeFactory::Once::create(AST_PERIOD_NODE);
    DFANode* functionDeclaration = DFANodeFactory::Once::createWithTarget(AST_FUNCTION_DECLARATION_NODE, AST_FUNCTION_DECLARATION_NODE);
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
    DFANode* procedureDeclaration = DFANodeFactory::Once::createWithTarget(AST_PROCEDURE_DECLARATION_NODE, AST_PROCEDURE_DECLARATION_NODE);
    DFANode* procedureKeyword = DFANodeFactory::Once::create(AST_PROCEDURE_NODE);
    DFANode* type = DFANodeFactory::Once::create(AST_TYPE_NODE);
    DFANode* varAssignment = DFANodeFactory::Once::create(AST_VARIABLE_ASSIGNMENT_NODE);
    DFANode* assignmentOperator = DFANodeFactory::Once::create(AST_ASSIGNMENT_OPERATOR_NODE);
    DFANode* varAssignmentStatement = DFANodeFactory::Once::createWithTarget(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE);
    DFANode* enumDeclaration = DFANodeFactory::Once::createWithTarget(AST_ENUM_DECLARATION_NODE, AST_ENUM_DECLARATION_NODE);
    DFANode* enumKeyword = DFANodeFactory::Once::create(AST_ENUM_NODE);
    DFANode* enumName = DFANodeFactory::Once::create(AST_ENUM_NAME_NODE);
    DFANode* enumKey = DFANodeFactory::Once::create(AST_ENUM_KEY_NODE);
    DFANode* enumKeyValue = DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_NODE);
    DFANode* enumKeyValueList = DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_LIST_NODE);
    DFANode* tupleKeyword = DFANodeFactory::Once::create(AST_TUPLE_NODE);
    DFANode* tupleItem = DFANodeFactory::Once::create(AST_TUPLE_ITEM_NODE);
    DFANode* tupleList = DFANodeFactory::Once::create(AST_TUPLE_LIST_NODE);
    DFANode* tupleExpression = DFANodeFactory::Once::create(AST_TUPLE_EXPRESSION_NODE);
    DFANode* tupleAccess = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_NODE);
    DFANode* tupleAccessExpression = DFANodeFactory::Once::create(AST_TUPLE_ACCESS_EXPRESSION_NODE);
    DFANode* objectAccessSource = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_SOURCE_NODE);
    DFANode* objectAccessTarget = DFANodeFactory::Once::create(AST_OBJECT_ACCESS_TARGET_NODE);

    this->initVarType(varType);
    this->initVarInit(varInit);
    this->initFunction(functionKeyword);
    this->initProcedure(procedureKeyword);
    this->initEnum(enumKeyword);

    logicalOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)));

    binaryOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)));

    unaryOperator
    ->reduceSelfWhenNextNodeIsOneOf({
            AST_GROUP_START_NODE,
            AST_FUNCTION_CALL_NODE,
            AST_IDENTIFIER_NODE
    })
//    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)));

    identifierExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE,
          AST_PERIOD_NODE
    })
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_TARGET_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(colon))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_ASSIGNMENT_NODE)));
    

    literalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
         AST_UNARY_OPERATOR_NODE
    })
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    arrayExpression
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));

    arrayAccessExpression
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_TARGET_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(period));

    objectAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
        AST_PERIOD_NODE
    })
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(period));

    binaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));
    

    logicalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator));
    

    unaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    arrayBase
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_ARRAY_EXPRESSION_NODE, { AST_VARIABLE_INIT_NODE, AST_COLON_NODE, AST_COMMA_NODE, AST_LEFT_BRACKET_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_ARRAY_ACCESS_NODE, {AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_EXPRESSION_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE, AST_TUPLE_ACCESS_EXPRESSION_NODE }));

    arrayAccess
    ->backtrackWhenLastReducedNodeIsOneOf({AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_EXPRESSION_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE });

    block
    ->markAlwaysReduceSelf();

    colon
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TYPE_NODE, AST_FUNCTION_PARAMETER_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)));

    period
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_NODE, AST_TUPLE_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_TARGET_NODE, AST_OBJECT_ACCESS_EXPRESSION_NODE)));

    functionKeyword
    ->markAlwaysReduceSelf();

    functionName
    ->markAlwaysReduceSelf();

    functionCall
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE)));

    functionParameter
    ->markAlwaysReduceSelf();

    functionParameterList
    ->markAlwaysReduceSelf();

    functionArgument
    ->markAlwaysReduceSelf();

    functionArgumentList
    ->markAlwaysReduceSelf();

    functionReturn
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)));

    functionReturnExpression
    ->markAlwaysReduceSelf();

    functionInvocationExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_TARGET_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(period))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));

    procedureKeyword
    ->markAlwaysReduceSelf();

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

    tupleKeyword
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_LIST_NODE, AST_TUPLE_EXPRESSION_NODE)));

    tupleItem
    ->markAlwaysReduceSelf();

    tupleList
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_TUPLE_NODE
    });

    tupleAccess
    ->markAlwaysReduceSelf();

    tupleAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE,
          AST_PERIOD_NODE
    })
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(period));

    type
    ->markAlwaysReduceSelf();

    varAssignment
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)));

    assignmentOperator
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_EXPRESSION_NODE });

    objectAccessSource
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_PERIOD_NODE })
    ->addTransition(DFATransitionFactory::create(period));

    objectAccessTarget
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_PERIOD_NODE });

    _dfa
    ->insertStartNode(varDeclaration)
    ->insertStartNode(varType)
    ->insertStartNode(varInit)
    ->insertStartNode(varAssignment)
    ->insertStartNode(assignmentOperator)
    ->insertStartNode(varAssignmentStatement)
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(identifierExpression)
    ->insertStartNode(literalExpression)
    ->insertStartNode(structExpression)
    ->insertStartNode(objectAccessExpression)
    ->insertStartNode(arrayExpression)
    ->insertStartNode(arrayAccessExpression)
    ->insertStartNode(binaryExpression)
    ->insertStartNode(logicalExpression)
    ->insertStartNode(unaryExpression)
    ->insertStartNode(functionInvocationExpression)
    ->insertStartNode(tupleExpression)
    ->insertStartNode(tupleAccessExpression)
    ->insertStartNode(DFANodeFactory::Once::create(AST_GROUP_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_END_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_LEFT_BRACKET_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_STRUCT_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_TUPLE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_COMMA_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_COLON_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_PERIOD_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(unaryOperator)
    ->insertStartNode(arrayBase)
    ->insertStartNode(arrayAccess)
    ->insertStartNode(structKeyValue)
    ->insertStartNode(block)
    ->insertStartNode(functionDeclaration)
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
    ->insertStartNode(procedureKeyword)
    ->insertStartNode(enumDeclaration)
    ->insertStartNode(enumKeyword)
    ->insertStartNode(enumName)
    ->insertStartNode(enumKey)
    ->insertStartNode(enumKeyValue)
    ->insertStartNode(enumKeyValueList)
    ->insertStartNode(tupleKeyword)
    ->insertStartNode(tupleItem)
    ->insertStartNode(tupleList)
    ->insertStartNode(tupleAccess)
    ->insertStartNode(type)
    ->insertStartNode(objectAccessSource)
    ->insertStartNode(objectAccessTarget)
    ->insertStartNode(DFANodeFactory::Once::create(AST_BINARY_OPERATOR_NODE)
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                          AST_BINARY_EXPRESSION_NODE,
                          AST_UNARY_EXPRESSION_NODE,
                          AST_LITERAL_EXPRESSION_NODE,
                          AST_IDENTIFIER_EXPRESSION_NODE
                      }))
    ->insertStartNode(DFANodeFactory::Once::create(logicalOperator->getNodeType())
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                          AST_BINARY_EXPRESSION_NODE,
                          AST_UNARY_EXPRESSION_NODE,
                          AST_LITERAL_EXPRESSION_NODE,
                          AST_IDENTIFIER_EXPRESSION_NODE
                      }));
}

void SyntaxDfa::initVarType(DFANode* varTypeNode) {
    varTypeNode
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_IDENTIFIER_NODE)
                    ->addTransition(
                            DFATransitionFactory::create(
                                DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_INIT_NODE)))
            )
    );
}

void SyntaxDfa::initVarInit(DFANode* varInitNode) {

    varInitNode
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_TUPLE_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)));

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
                                                                    DFANodeFactory::Once::create(AST_TYPE_NODE)
                                                                        ->addTransition(
                                                                            DFATransitionFactory::create(
                                                                                DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_FUNCTION_DECLARATION_NODE)
                                                                        ))
                                                        ))
                                                    ))
                    )
            );
}

void SyntaxDfa::initProcedure(DFANode* procedureNode) {
    procedureNode
            ->addTransition(
                    DFATransitionFactory::create(
                            DFANodeFactory::Once::create(AST_FUNCTION_NAME_NODE)
                                    ->addTransition(
                                            DFATransitionFactory::create(
                                                    DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_NODE)
                                                    ->addTransition(
                                                            DFATransitionFactory::create(
                                                                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_PROCEDURE_DECLARATION_NODE)
                                                            ))
                                            ))
                    )
            );
}

void SyntaxDfa::initEnum(DFANode* enumNode) {
    enumNode
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