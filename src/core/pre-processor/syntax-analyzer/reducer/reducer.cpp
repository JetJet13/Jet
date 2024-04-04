//
// Created by Johny Georges on 2024-02-08.
//

#include "reducer.h"
#include "reducer-strategies/variable-init-reducer-strategy/variable-init-reducer-strategy.h"
#include "reducer-strategies/variable-declaration-reducer-strategy/variable-declaration-reducer-strategy.h"
#include "reducer-strategies/unary-expression-reducer-strategy/unary-expression-reducer-strategy.h"
#include "reducer-strategies/binary-expression-reducer-strategy/binary-expression-reducer-strategy.h"
#include "reducer-strategies/logical-expression-reducer-strategy/logical-expression-reducer-strategy.h"
#include "reducer-strategies/identifier-expression-reducer-strategy/identifier-expression-reducer-strategy.h"
#include "reducer-strategies/literal-expression-reducer-strategy/literal-expression-reducer-strategy.h"
#include "reducer-strategies/array-access-expression-reducer-strategy/array-access-expression-reducer-strategy.h"
#include "reducer-strategies/array-expression-reducer-strategy/array-expression-reducer-strategy.h"
#include "reducer-strategies/array-access-reducer-strategy/array-access-reducer-strategy.h"
#include "reducer-strategies/array-node-reducer-strategy/array-node-reducer-strategy.h"
#include "reducer-strategies/struct-key-value-reducer-strategy/struct-key-value-reducer-strategy.h"
#include "reducer-strategies/struct-expression-reducer-strategy/struct-expression-reducer-strategy.h"
#include "reducer-strategies/block-reducer-strategy/block-reducer-strategy.h"
#include "reducer-strategies/object-access-expression-reducer-strategy/object-access-expression-reducer-strategy.h"
#include "reducer-strategies/function-declaration-reducer-strategy/function-declaration-reducer-strategy.h"
#include "reducer-strategies/function-parameter-list-reducer-strategy/function-parameter-list-reducer-strategy.h"
#include "reducer-strategies/function-return-expression-reducer-strategy/function-return-expression-reducer-strategy.h"
#include "reducer-strategies/function-parameter-reducer-strategy/function-parameter-reducer-strategy.h"
#include "reducer-strategies/variable-assignment-statement-reducer-strategy/variable-assignment-statement-reducer-strategy.h"
#include "reducer-strategies/variable-assignment-reducer-strategy/variable-assignment-reducer-strategy.h"
#include "reducer-strategies/procedure-declaration-reducer-strategy/procedure-declaration-reducer-strategy.h"
#include "reducer-strategies/enum-key-reducer-strategy/enum-key-reducer-strategy.h"
#include "reducer-strategies/enum-key-value-reducer-strategy/enum-key-value-reducer-strategy.h"
#include "reducer-strategies/enum-key-value-list-reducer-strategy/enum-key-value-list-reducer-strategy.h"
#include "reducer-strategies/enum-declaration-reducer-strategy/enum-declaration-reducer-strategy.h"
#include "reducer-strategies/function-invocation-expression-reducer-strategy/function-invocation-expression-reducer-strategy.h"
#include "reducer-strategies/function-argument-list-reducer-strategy/function-argument-list-reducer-strategy.h"
#include "reducer-strategies/expression-statement-reducer-strategy/expression-statement-reducer-strategy.h"
#include "reducer-strategies/tuple-list-reducer-strategy/tuple-list-reducer-strategy.h"
#include "reducer-strategies/tuple-expression-reducer-strategy/tuple-expression-reducer-strategy.h"
#include "reducer-strategies/tuple-access-expression-reducer-strategy/tuple-access-expression-reducer-strategy.h"
#include "reducer-strategies/object-access-source-reducer-strategy/object-access-source-reducer-strategy.h"
#include "reducer-strategies/object-access-target-reducer-strategy/object-access-target-reducer-strategy.h"
#include "reducer-strategies/control-flow-condition-reducer-strategy/control-flow-condition-reducer-strategy.h"
#include "reducer-strategies/if-block-reducer-strategy/if-block-reducer-strategy.h"
#include "reducer-strategies/else-block-reducer-strategy/else-block-reducer-strategy.h"
#include "reducer-strategies/else-if-reducer-strategy/else-if-reducer-strategy.h"
#include "reducer-strategies/else-if-block-reducer-strategy/else-if-block-reducer-strategy.h"
#include "reducer-strategies/while-statement-reducer-strategy/while-statement-reducer-strategy.h"
#include "reducer-strategies/for-statement-reducer-strategy/for-statement-reducer-strategy.h"
#include "reducer-strategies/for-variable-reducer-strategy/for-variable-reducer-strategy.h"
#include "reducer-strategies/for-source-reducer-strategy/for-source-reducer-strategy.h"
#include "reducer-strategies/if-statement-reducer-strategy/if-statement-reducer-strategy.h"
#include "reducer-strategies/try-statement-reducer-strategy/try-statement-reducer-strategy.h"
#include "reducer-strategies/finally-block-reducer-strategy/finally-block-reducer-strategy.h"
#include "reducer-strategies/catch-block-reducer-strategy/catch-block-reducer-strategy.h"
#include "reducer-strategies/try-block-reducer-strategy/try-block-reducer-strategy.h"
#include "reducer-strategies/lambda-expression-reducer-strategy/lambda-expression-reducer-strategy.h"
#include "reducer-strategies/lambda-return-expression-reducer-strategy/lambda-return-expression-reducer-strategy.h"

Reducer::Reducer() {
    _strategies = std::unordered_map<ASTNodeType, ReducerStrategy*, std::hash<int>>();
    this->initStrategies();
}

void Reducer::initStrategies() {
    this->addStrategy(AST_VARIABLE_INIT_NODE, new VariableInitReducerStrategy());
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, new VariableDeclarationReducerStrategy());
    this->addStrategy(AST_UNARY_EXPRESSION_NODE, new UnaryExpressionReducerStrategy());
    this->addStrategy(AST_BINARY_EXPRESSION_NODE, new BinaryExpressionReducerStrategy());
    this->addStrategy(AST_LOGICAL_EXPRESSION_NODE, new LogicalExpressionReducerStrategy());
    this->addStrategy(AST_IDENTIFIER_EXPRESSION_NODE, new IdentifierExpressionReducerStrategy());
    this->addStrategy(AST_LITERAL_EXPRESSION_NODE, new LiteralExpressionReducerStrategy());
    this->addStrategy(AST_ARRAY_NODE, new ArrayNodeReducerStrategy());
    this->addStrategy(AST_ARRAY_ACCESS_EXPRESSION_NODE, new ArrayAccessExpressionReducerStrategy());
    this->addStrategy(AST_ARRAY_ACCESS_NODE, new ArrayAccessReducerStrategy());
    this->addStrategy(AST_ARRAY_EXPRESSION_NODE, new ArrayExpressionReducerStrategy());
    this->addStrategy(AST_BLOCK_NODE, new BlockReducerStrategy());
    this->addStrategy(AST_STRUCT_KEY_VALUE_NODE, new StructKeyValueReducerStrategy());
    this->addStrategy(AST_STRUCT_EXPRESSION_NODE, new StructExpressionReducerStrategy());
    this->addStrategy(AST_OBJECT_ACCESS_EXPRESSION_NODE, new ObjectAccessExpressionReducerStrategy());
    this->addStrategy(AST_FUNCTION_DECLARATION_NODE, new FunctionDeclarationReducerStrategy());
    this->addStrategy(AST_FUNCTION_PARAMETER_LIST_NODE, new FunctionParameterListReducerStrategy());
    this->addStrategy(AST_FUNCTION_PARAMETER_NODE, new FunctionParameterReducerStrategy());
    this->addStrategy(AST_FUNCTION_RETURN_EXPRESSION_NODE, new FunctionReturnExpressionReducerStrategy());
    this->addStrategy(AST_PROCEDURE_DECLARATION_NODE, new ProcedureDeclarationReducerStrategy());
    this->addStrategy(AST_FUNCTION_ARGUMENT_LIST_NODE, new FunctionArgumentListReducerStrategy());
    this->addStrategy(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, new FunctionInvocationExpressionReducerStrategy());
    this->addStrategy(AST_VARIABLE_ASSIGNMENT_NODE, new VariableAssignmentReducerStrategy());
    this->addStrategy(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE, new VariableAssignmentStatementReducerStrategy());
    this->addStrategy(AST_ENUM_KEY_NODE, new EnumKeyReducerStrategy());
    this->addStrategy(AST_ENUM_KEY_VALUE_NODE, new EnumKeyValueReducerStrategy());
    this->addStrategy(AST_ENUM_KEY_VALUE_LIST_NODE, new EnumKeyValueListReducerStrategy());
    this->addStrategy(AST_ENUM_DECLARATION_NODE, new EnumDeclarationReducerStrategy());
    this->addStrategy(AST_EXPRESSION_STATEMENT_NODE, new ExpressionStatementReducerStrategy());
    this->addStrategy(AST_TUPLE_LIST_NODE, new TupleListReducerStrategy());
    this->addStrategy(AST_TUPLE_EXPRESSION_NODE, new TupleExpressionReducerStrategy());
    this->addStrategy(AST_TUPLE_ACCESS_EXPRESSION_NODE, new TupleAccessExpressionReducerStrategy());
    this->addStrategy(AST_OBJECT_ACCESS_SOURCE_NODE, new ObjectAccessSourceReducerStrategy());
    this->addStrategy(AST_OBJECT_ACCESS_TARGET_NODE, new ObjectAccessTargetReducerStrategy());
    this->addStrategy(AST_CONTROL_FLOW_CONDITION_NODE, new ControlFlowConditionReducerStrategy());
    this->addStrategy(AST_IF_BLOCK_NODE, new IfBlockReducerStrategy());
    this->addStrategy(AST_ELSE_IF_BLOCK_NODE, new ElseIfBlockReducerStrategy());
    this->addStrategy(AST_ELSE_BLOCK_NODE, new ElseBlockReducerStrategy());
    this->addStrategy(AST_ELSE_IF_NODE, new ElseIfReducerStrategy());
    this->addStrategy(AST_IF_STATEMENT_NODE, new IfStatementReducerStrategy());
    this->addStrategy(AST_WHILE_STATEMENT_NODE, new WhileStatementReducerStrategy());
    this->addStrategy(AST_FOR_VARIABLE_NODE, new ForVariableReducerStrategy());
    this->addStrategy(AST_FOR_SOURCE_NODE, new ForSourceReducerStrategy());
    this->addStrategy(AST_FOR_STATEMENT_NODE, new ForStatementReducerStrategy());
    this->addStrategy(AST_TRY_STATEMENT_NODE, new TryStatementReducerStrategy());
    this->addStrategy(AST_TRY_BLOCK_NODE, new TryBlockReducerStrategy());
    this->addStrategy(AST_CATCH_BLOCK_NODE, new CatchBlockReducerStrategy());
    this->addStrategy(AST_FINALLY_BLOCK_NODE, new FinallyBlockReducerStrategy());
    this->addStrategy(AST_LAMBDA_EXPRESSION_NODE, new LambdaExpressionReducerStrategy());
    this->addStrategy(AST_LAMBDA_RETURN_EXPRESSION_NODE, new LambdaReturnExpressionReducerStrategy());
}

void Reducer::addStrategy(ASTNodeType astNodeType, ReducerStrategy* reducerStrategy) {
    _strategies.insert(std::pair<ASTNodeType, ReducerStrategy*>(astNodeType, reducerStrategy));
}


ASTNode* Reducer::reduce(Handle handle, RecognizerResult* recognizerResult) {
    if (handle.isEmpty()) {
        throw std::invalid_argument("handle cannot be empty");
    }

    if (recognizerResult->getNumReducedNodes() == 1 && handle.isNodeTypeAt(0, recognizerResult->getTargetAstNodeType())) {
        return handle.at(0).value();
    }

    auto nodesToReduce = handle.getFirstNodes(recognizerResult->getNumReducedNodes());

    return this->generateASTNode(recognizerResult->getTargetAstNodeType(), nodesToReduce);
}

ASTNode* Reducer::generateASTNode(ASTNodeType targetAstNodeType, std::vector<ASTNode*> nodes) {
    auto reducerStrategy = _strategies.find(targetAstNodeType);
    if (reducerStrategy == _strategies.end()) {
        throw std::invalid_argument("unable to determine reduced AST Node Type for given list of nodes");
    }
    return reducerStrategy->second->execute(nodes);
}
