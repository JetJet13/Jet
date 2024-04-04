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
    DFANode* forSource = DFANodeFactory::Once::create(AST_FOR_SOURCE_NODE);
    DFANode* forVariable = DFANodeFactory::Once::create(AST_FOR_VARIABLE_NODE);
    DFANode* forStatement = DFANodeFactory::Once::createWithTarget(AST_FOR_STATEMENT_NODE, AST_FOR_STATEMENT_NODE);
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
    DFANode* fatArrow = DFANodeFactory::Once::create(AST_FAT_ARROW_NODE);
    DFANode* lambdaReturnExpression = DFANodeFactory::Once::create(AST_LAMBDA_RETURN_EXPRESSION_NODE);
    DFANode* lambdaExpression = DFANodeFactory::Once::create(AST_LAMBDA_EXPRESSION_NODE);

    // todo: implement lambda expression ast-node + reducer strategy;
    // example syntax:
    // const lambda = (x: IdType, y: IdType) => x.val + y.val;
    // const lambda = (x: int, y: int) => x > y;
    // const lambda = (x: int) int { return x + 10 };
    // todo: implement function type
    // example syntax:
    // (int) => bool
    // (int, int) => CustomType
    // (int) => (int) => bool
    // (int) => (int) => (int) => Money

    this->initVarType(varType);
    this->initVarInit(varInit);
    this->initFunction(functionKeyword);
    this->initProcedure(procedureKeyword);
    this->initEnum(enumKeyword);
    this->initIf(ifKeyword);
    this->initElse(elseKeyword);
    this->initElseIf(elseIfKeyword);
    this->initWhile(whileKeyword);
    this->initFor(forKeyword);

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
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_VARIABLE_NODE, { AST_FOR_NODE }, { AST_FOR_IN_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(colon))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_ASSIGNMENT_NODE)));


    literalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
         AST_UNARY_OPERATOR_NODE
    })
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    arrayExpression
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));

    arrayAccessExpression
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(period));

    objectAccessExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE,
        AST_PERIOD_NODE
    })
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(period));

    binaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));


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
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
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
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_ARGUMENT_LIST_NODE, AST_FUNCTION_INVOCATION_EXPRESSION_NODE)));

    functionParameter
    ->markAlwaysReduceSelf();

    functionParameterList
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_FUNCTION_NAME_NODE })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LAMBDA_RETURN_EXPRESSION_NODE, AST_LAMBDA_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_LAMBDA_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(
            DFANodeFactory::Once::create(AST_TYPE_NODE)
            ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LAMBDA_RETURN_EXPRESSION_NODE, AST_LAMBDA_EXPRESSION_NODE)))
            ->addTransition(DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FUNCTION_BLOCK_NODE, AST_LAMBDA_EXPRESSION_NODE)))
    ));

    functionArgument
    ->markAlwaysReduceSelf();

    functionArgumentList
    ->markAlwaysReduceSelf();

    functionReturn
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LAMBDA_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
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
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
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
          AST_UNARY_OPERATOR_NODE
    })
    ->addReduceToTargetMapForNextNode(new ReduceToTargetMap(AST_OBJECT_ACCESS_SOURCE_NODE, { AST_PERIOD_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_CONTROL_FLOW_CONDITION_NODE, { AST_IF_NODE, AST_ELSE_IF_NODE, AST_WHILE_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addReduceToTargetMapForPrevNodeAndNextNode(new ReduceToTargetDualMap(AST_FOR_SOURCE_NODE, { AST_FOR_IN_NODE }, { AST_CONTROL_FLOW_START_NODE }))
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(period));

    type
    ->markAlwaysReduceSelf();

    varAssignment
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LAMBDA_EXPRESSION_NODE, AST_FUNCTION_RETURN_EXPRESSION_NODE)))
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
            DFANodeFactory::NilOrMore::create(AST_ELSE_IF_BLOCK_NODE)
            ->addTransition(DFATransitionFactory::create(DFANodeFactory::NilOrOnce::createWithTarget(AST_ELSE_BLOCK_NODE, AST_IF_STATEMENT_NODE)))
    ));

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
                DFANodeFactory::NilOrOnce::createWithTarget(AST_FINALLY_BLOCK_NODE, AST_TRY_STATEMENT_NODE)
            ))
    ));

    catchBlock
    ->reduceSelfWhenNextNodeIsOneOf({ AST_FINALLY_NODE })
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_TRY_BLOCK_NODE });

    finallyBlock
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_CATCH_BLOCK_NODE });

    fatArrow
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_OBJECT_ACCESS_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LAMBDA_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_TUPLE_ACCESS_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_LAMBDA_RETURN_EXPRESSION_NODE)));

    lambdaReturnExpression
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE });

    lambdaExpression
    ->markAlwaysReduceSelf();

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
    ->insertStartNode(lambdaExpression)
    ->insertStartNode(DFANodeFactory::Once::create(AST_GROUP_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_END_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_LEFT_BRACKET_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_STRUCT_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_FUNCTION_PARAMETER_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_FUNCTION_ARGUMENT_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_ENUM_KEY_VALUE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_TUPLE_LIST_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_CONTROL_FLOW_START_NODE)->markAlwaysReduceSelf())
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
    ->insertStartNode(fatArrow)
    ->insertStartNode(lambdaReturnExpression)
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
                    DFANodeFactory::Once::createWithTarget(AST_LAMBDA_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
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
                            DFANodeFactory::Once::create(AST_FOR_VARIABLE_NODE)
                                    ->addTransition(
                                            DFATransitionFactory::create(
                                                    DFANodeFactory::Once::create(AST_FOR_IN_NODE)
                                                            ->addTransition(
                                                                    DFATransitionFactory::create(
                                                                            DFANodeFactory::Once::create(AST_FOR_SOURCE_NODE)
                                                                                    ->addTransition(
                                                                                            DFATransitionFactory::create(
                                                                                                    DFANodeFactory::Once::createWithTarget(AST_CONTROL_FLOW_BLOCK_NODE, AST_FOR_STATEMENT_NODE)
                                                                                            ))
                                                                    ))
                                            ))
                    )
            );
}