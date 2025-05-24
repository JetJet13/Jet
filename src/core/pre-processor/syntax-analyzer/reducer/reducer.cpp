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
#include "reducer-strategies/for-in-statement-reducer-strategy/for-in-statement-reducer-strategy.h"
#include "reducer-strategies/for-in-variable-reducer-strategy/for-in-variable-reducer-strategy.h"
#include "reducer-strategies/for-in-source-reducer-strategy/for-in-source-reducer-strategy.h"
#include "reducer-strategies/if-statement-reducer-strategy/if-statement-reducer-strategy.h"
#include "reducer-strategies/try-statement-reducer-strategy/try-statement-reducer-strategy.h"
#include "reducer-strategies/finally-block-reducer-strategy/finally-block-reducer-strategy.h"
#include "reducer-strategies/catch-block-reducer-strategy/catch-block-reducer-strategy.h"
#include "reducer-strategies/try-block-reducer-strategy/try-block-reducer-strategy.h"
#include "reducer-strategies/lambda-expression-reducer-strategy/lambda-expression-reducer-strategy.h"
#include "reducer-strategies/lambda-return-expression-reducer-strategy/lambda-return-expression-reducer-strategy.h"
#include "reducer-strategies/type-parameter-list-reducer-strategy/type-parameter-list-reducer-strategy.h"
#include "reducer-strategies/lambda-function-type-parameter-list-reducer-strategy/lambda-function-type-parameter-list-reducer-strategy.h"
#include "reducer-strategies/lambda-procedure-type-parameter-list-reducer-strategy/lambda-procedure-type-parameter-list-reducer-strategy.h"
#include "reducer-strategies/curry-expression-reducer-strategy/curry-expression-reducer-strategy.h"
#include "reducer-strategies/tuple-type-reducer-strategy/tuple-type-reducer-strategy.h"
#include "reducer-strategies/array-type-reducer-strategy/array-type-reducer-strategy.h"
#include "reducer-strategies/variable-definition-reducer-strategy/variable-definition-reducer-strategy.h"
#include "reducer-strategies/module-list-alias-item-reducer-strategy/module-list-alias-item-reducer-strategy.h"
#include "reducer-strategies/module-list-spread-item-reducer-strategy/module-list-spread-item-reducer-strategy.h"
#include "reducer-strategies/module-list-reducer-strategy/module-list-reducer-strategy.h"
#include "reducer-strategies/module-declaration-reducer-strategy/module-declaration-reducer-strategy.h"
#include "reducer-strategies/import-single-module-declaration-reducer-strategy/import-single-module-declaration-reducer-strategy.h"
#include "reducer-strategies/use-single-module-declaration-reducer-strategy/use-single-module-declaration-reducer-strategy.h"
#include "reducer-strategies/import-many-module-declaration-reducer-strategy/import-many-module-declaration-reducer-strategy.h"
#include "reducer-strategies/import-module-list-by-wildcard-item-reducer-strategy/import-module-list-by-wildcard-item-reducer-strategy.h"
#include "reducer-strategies/use-many-module-declaration-reducer-strategy/use-many-module-declaration-reducer-strategy.h"
#include "reducer-strategies/import-module-list-by-group-item-reducer-strategy/import-module-list-by-group-item-reducer-strategy.h"
#include "reducer-strategies/import-module-list-alias-item-reducer-strategy/import-module-list-alias-item-reducer-strategy.h"
#include "reducer-strategies/import-module-list-spread-item-reducer-strategy/import-module-list-spread-item-reducer-strategy.h"
#include "reducer-strategies/import-module-list-reducer-strategy/import-module-list-reducer-strategy.h"
#include "reducer-strategies/class-declaration-reducer-strategy/class-declaration-reducer-strategy.h"
#include "reducer-strategies/class-property-declaration-reducer-strategy/class-property-declaration-reducer-strategy.h"
#include "reducer-strategies/class-constructor-declaration-reducer-strategy/class-constructor-declaration-reducer-strategy.h"
#include "reducer-strategies/class-method-declaration-reducer-strategy/class-method-declaration-reducer-strategy.h"
#include "reducer-strategies/class-property-definition-reducer-strategy/class-property-definition-reducer-strategy.h"
#include "reducer-strategies/class-property-init-reducer-strategy/class-property-init-reducer-strategy.h"
#include "reducer-strategies/class-property-definition-with-type-reducer-strategy/class-property-definition-with-type-reducer-strategy.h"
#include "reducer-strategies/class-property-assignment-reducer-strategy/class-property-assignment-reducer-strategy.h"
#include "reducer-strategies/class-property-access-reducer-strategy/class-property-access-reducer-strategy.h"
#include "reducer-strategies/class-property-assignment-statement-node/class-property-assignment-statement-node.h"
#include "reducer-strategies/class-method-invocation-expression-reducer-strategy/class-method-invocation-expression-reducer-strategy.h"
#include "reducer-strategies/class-access-reducer-strategy/class-access-reducer-strategy.h"
#include "reducer-strategies/new-class-instance-expression-reducer-strategy/new-class-instance-expression-reducer-strategy.h"
#include "reducer-strategies/class-method-definition-reducer-strategy/class-method-definition-reducer-strategy.h"
#include "reducer-strategies/class-property-access-expression-reducer-strategy/class-property-access-expression-reducer-strategy.h"
#include "reducer-strategies/this-expression-reducer-strategy/this-expression-reducer-strategy.h"
#include "reducer-strategies/procedure-type-reducer-strategy/procedure-type-reducer-strategy.h"
#include "reducer-strategies/function-type-reducer-strategy/function-type-reducer-strategy.h"
#include "reducer-strategies/lambda-with-fat-arrow-expression-reducer-strategy/lambda-with-fat-arrow-expression-reducer-strategy.h"
#include "reducer-strategies/import-many-by-wildcard-module-declaration-reducer-strategy/import-many-by-wildcard-module-declaration-reducer-strategy.h"
#include "reducer-strategies/use-many-by-wildcard-module-declaration-reducer-strategy/use-many-by-wildcard-module-declaration-reducer-strategy.h"
#include "reducer-strategies/function-definition-reducer-strategy/function-definition-reducer-strategy.h"
#include "reducer-strategies/procedure-definition-reducer-strategy/procedure-definition-reducer-strategy.h"
#include "reducer-strategies/module-access-expression-reducer-strategy/module-access-expression-reducer-strategy.h"
#include "reducer-strategies/module-access-source-reducer-strategy/module-access-source-reducer-strategy.h"
#include "reducer-strategies/module-access-target-reducer-strategy/module-access-target-reducer-strategy.h"
#include "reducer-strategies/callable-identifier-expression-reducer-strategy/callable-identifier-expression-reducer-strategy.h"
#include "reducer-strategies/ref-expression-reducer-strategy/ref-expression-reducer-strategy.h"
#include "reducer-strategies/dref-expression-strategy/dref-expression-strategy.h"
#include "reducer-strategies/ref-type-reducer-strategy/ref-type-reducer-strategy.h"
#include "reducer-strategies/array-access-assignment-reducer-strategy/array-access-assignment-reducer-strategy.h"
#include "reducer-strategies/array-access-assignment-statement-reducer-strategy/array-access-assignment-statement-reducer-strategy.h"
#include "reducer-strategies/sref-expression-reducer-strategy/sref-expression-reducer-strategy.h"

Reducer::Reducer() {
    _strategies = std::unordered_map<ASTNodeType, ReducerStrategy*, std::hash<int>>();
    this->initStrategies();
}

void Reducer::initStrategies() {
    this->addStrategy(AST_VARIABLE_INIT_NODE, new VariableInitReducerStrategy());
    this->addStrategy(AST_VARIABLE_DEFINITION_NODE, new VariableDefinitionReducerStrategy());
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, new VariableDeclarationReducerStrategy());
    this->addStrategy(AST_UNARY_EXPRESSION_NODE, new UnaryExpressionReducerStrategy());
    this->addStrategy(AST_BINARY_EXPRESSION_NODE, new BinaryExpressionReducerStrategy());
    this->addStrategy(AST_LOGICAL_EXPRESSION_NODE, new LogicalExpressionReducerStrategy());
    this->addStrategy(AST_IDENTIFIER_EXPRESSION_NODE, new IdentifierExpressionReducerStrategy());
    this->addStrategy(AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE, new CallableIdentifierExpressionReducerStrategy());
    this->addStrategy(AST_LITERAL_EXPRESSION_NODE, new LiteralExpressionReducerStrategy());
    this->addStrategy(AST_ARRAY_NODE, new ArrayNodeReducerStrategy());
    this->addStrategy(AST_ARRAY_ACCESS_EXPRESSION_NODE, new ArrayAccessExpressionReducerStrategy());
    this->addStrategy(AST_ARRAY_ACCESS_NODE, new ArrayAccessReducerStrategy());
    this->addStrategy(AST_ARRAY_ACCESS_ASSIGNMENT_NODE, new ArrayAccessAssignmentReducerStrategy());
    this->addStrategy(AST_ARRAY_EXPRESSION_NODE, new ArrayExpressionReducerStrategy());
    this->addStrategy(AST_STRUCT_KEY_VALUE_NODE, new StructKeyValueReducerStrategy());
    this->addStrategy(AST_STRUCT_EXPRESSION_NODE, new StructExpressionReducerStrategy());
    this->addStrategy(AST_OBJECT_ACCESS_EXPRESSION_NODE, new ObjectAccessExpressionReducerStrategy());
    this->addStrategy(AST_MODULE_ACCESS_EXPRESSION_NODE, new ModuleAccessExpressionReducerStrategy());
    this->addStrategy(AST_FUNCTION_DECLARATION_NODE, new FunctionDeclarationReducerStrategy());
    this->addStrategy(AST_FUNCTION_DEFINITION_NODE, new FunctionDefinitionReducerStrategy());
    this->addStrategy(AST_FUNCTION_PARAMETER_LIST_NODE, new FunctionParameterListReducerStrategy());
    this->addStrategy(AST_FUNCTION_PARAMETER_NODE, new FunctionParameterReducerStrategy());
    this->addStrategy(AST_FUNCTION_RETURN_EXPRESSION_NODE, new FunctionReturnExpressionReducerStrategy());
    this->addStrategy(AST_PROCEDURE_DECLARATION_NODE, new ProcedureDeclarationReducerStrategy());
    this->addStrategy(AST_PROCEDURE_DEFINITION_NODE, new ProcedureDefinitionReducerStrategy());
    this->addStrategy(AST_FUNCTION_ARGUMENT_LIST_NODE, new FunctionArgumentListReducerStrategy());
    this->addStrategy(AST_FUNCTION_INVOCATION_EXPRESSION_NODE, new FunctionInvocationExpressionReducerStrategy());
    this->addStrategy(AST_VARIABLE_ASSIGNMENT_NODE, new VariableAssignmentReducerStrategy());
    this->addStrategy(AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE, new VariableAssignmentStatementReducerStrategy());
    this->addStrategy(AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE, new ArrayAccessAssignmentStatementReducerStrategy());
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
    this->addStrategy(AST_MODULE_ACCESS_SOURCE_NODE, new ModuleAccessSourceReducerStrategy());
    this->addStrategy(AST_MODULE_ACCESS_TARGET_NODE, new ModuleAccessTargetReducerStrategy());
    this->addStrategy(AST_CONTROL_FLOW_CONDITION_NODE, new ControlFlowConditionReducerStrategy());
    this->addStrategy(AST_IF_BLOCK_NODE, new IfBlockReducerStrategy());
    this->addStrategy(AST_ELSE_IF_BLOCK_NODE, new ElseIfBlockReducerStrategy());
    this->addStrategy(AST_ELSE_BLOCK_NODE, new ElseBlockReducerStrategy());
    this->addStrategy(AST_ELSE_IF_NODE, new ElseIfReducerStrategy());
    this->addStrategy(AST_IF_STATEMENT_NODE, new IfStatementReducerStrategy());
    this->addStrategy(AST_WHILE_STATEMENT_NODE, new WhileStatementReducerStrategy());
    this->addStrategy(AST_FOR_IN_VARIABLE_NODE, new ForInVariableReducerStrategy());
    this->addStrategy(AST_FOR_IN_SOURCE_NODE, new ForInSourceReducerStrategy());
    this->addStrategy(AST_FOR_IN_STATEMENT_NODE, new ForInStatementReducerStrategy());
    this->addStrategy(AST_TRY_STATEMENT_NODE, new TryStatementReducerStrategy());
    this->addStrategy(AST_TRY_BLOCK_NODE, new TryBlockReducerStrategy());
    this->addStrategy(AST_CATCH_BLOCK_NODE, new CatchBlockReducerStrategy());
    this->addStrategy(AST_FINALLY_BLOCK_NODE, new FinallyBlockReducerStrategy());
    this->addStrategy(AST_LAMBDA_EXPRESSION_NODE, new LambdaExpressionReducerStrategy());
    this->addStrategy(AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE, new LambdaWithFatArrowExpressionReducerStrategy());
    this->addStrategy(AST_LAMBDA_RETURN_EXPRESSION_NODE, new LambdaReturnExpressionReducerStrategy());
    this->addStrategy(AST_TYPE_PARAMETER_LIST_NODE, new TypeParameterListReducerStrategy());
    this->addStrategy(AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE, new LambdaFunctionTypeParameterListReducerStrategy());
    this->addStrategy(AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE, new LambdaProcedureTypeParameterListReducerStrategy());
    this->addStrategy(AST_PROCEDURE_TYPE_NODE, new ProcedureTypeReducerStrategy());
    this->addStrategy(AST_FUNCTION_TYPE_NODE, new FunctionTypeReducerStrategy());
    this->addStrategy(AST_CURRY_EXPRESSION_NODE, new CurryExpressionReducerStrategy());
    this->addStrategy(AST_TUPLE_TYPE_NODE, new TupleTypeReducerStrategy());
    this->addStrategy(AST_ARRAY_TYPE_NODE, new ArrayTypeReducerStrategy());
    this->addStrategy(AST_MODULE_LIST_ALIAS_ITEM_NODE, new ModuleListAliasItemReducerStrategy());
    this->addStrategy(AST_MODULE_LIST_SPREAD_ITEM_NODE, new ModuleListSpreadItemReducerStrategy());
    this->addStrategy(AST_MODULE_LIST_NODE, new ModuleListReducerStrategy());
    this->addStrategy(AST_MODULE_DECLARATION_NODE, new ModuleDeclarationReducerStrategy());
    this->addStrategy(AST_USE_SINGLE_MODULE_DECLARATION_NODE, new UseSingleModuleDeclarationReducerStrategy());
    this->addStrategy(AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE, new ImportSingleModuleDeclarationReducerStrategy());
    this->addStrategy(AST_IMPORT_MANY_MODULE_DECLARATION_NODE, new ImportManyModuleDeclarationReducerStrategy());
    this->addStrategy(AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE, new ImportManyByWildcardModuleDeclarationReducerStrategy());
    this->addStrategy(AST_USE_MANY_MODULE_DECLARATION_NODE, new UseManyModuleDeclarationReducerStrategy());
    this->addStrategy(AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE, new UseManyByWildcardModuleDeclarationReducerStrategy());
    this->addStrategy(AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE, new ImportModuleListByWildcardItemReducerStrategy());
    this->addStrategy(AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE, new ImportModuleListByGroupItemReducerStrategy());
    this->addStrategy(AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE, new ImportModuleListAliasItemReducerStrategy());
    this->addStrategy(AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE, new ImportModuleListSpreadItemReducerStrategy());
    this->addStrategy(AST_IMPORT_MODULE_LIST_NODE, new ImportModuleListReducerStrategy());
    this->addStrategy(AST_CLASS_DECLARATION_NODE, new ClassDeclarationReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_DECLARATION_NODE, new ClassPropertyDeclarationReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_ACCESS_NODE, new ClassPropertyAccessReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_ASSIGNMENT_NODE, new ClassPropertyAssignmentReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE, new ClassPropertyAssignmentStatementReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_DEFINITION_NODE, new ClassPropertyDefinitionReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE, new ClassPropertyDefinitionWithTypeReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_INIT_NODE, new ClassPropertyInitReducerStrategy());
    this->addStrategy(AST_CLASS_CONSTRUCTOR_DECLARATION_NODE, new ClassConstructorDeclarationReducerStrategy());
    this->addStrategy(AST_CLASS_METHOD_DECLARATION_NODE, new ClassMethodDeclarationReducerStrategy());
    this->addStrategy(AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE, new ClassMethodInvocationExpressionReducerStrategy());
    this->addStrategy(AST_CLASS_METHOD_DEFINITION_NODE, new ClassMethodDefinitionReducerStrategy());
    this->addStrategy(AST_CLASS_ACCESS_NODE, new ClassAccessReducerStrategy());
    this->addStrategy(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE, new NewClassInstanceExpressionReducerStrategy());
    this->addStrategy(AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE, new ClassPropertyAccessExpressionReducerStrategy());
    this->addStrategy(AST_THIS_EXPRESSION_NODE, new ThisExpressionReducerStrategy());
    this->addStrategy(AST_REF_EXPRESSION_NODE, new RefExpressionReducerStrategy());
    this->addStrategy(AST_DREF_EXPRESSION_NODE, new DrefExpressionReducerStrategy());
    this->addStrategy(AST_SREF_EXPRESSION_NODE, new SrefExpressionReducerStrategy());
    this->addStrategy(AST_REF_TYPE_NODE, new RefTypeReducerStrategy());
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
