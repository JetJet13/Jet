//
// Created by Johny Georges on 2024-05-21.
//

#include "type-checker.h"
#include "policies/procedure-declaration-type-checker-policy/procedure-declaration-type-checker-policy.h"
#include "policies/variable-declaration-type-checker-policy/variable-declaration-type-checker-policy.h"
#include "policies/parameter-list-type-checker-policy/parameter-list-type-checker-policy.h"
#include "policies/parameter-type-checker-policy/parameter-type-checker-policy.h"
#include "policies/function-declaration-type-checker-policy/function-declaration-type-checker-policy.h"
#include "policies/function-block-type-checker-policy/function-block-type-checker-policy.h"
#include "policies/expressions/function-return-expression-type-checker-policy/function-return-expression-type-checker-policy.h"
#include "policies/variable-assignment-statement-type-checker-policy/variable-assignment-statement-type-checker-policy.h"
#include "policies/enum-declaration-type-checker-policy/enum-declaration-type-checker-policy.h"
#include "policies/class-declaration-type-checker-policy/class-declaration-type-checker-policy.h"
#include "policies/if-statement-type-checker-policy/if-statement-type-checker-policy.h"
#include "policies/try-statement-type-checker-policy/try-statement-type-checker-policy.h"
#include "policies/for-in-statement-type-checker-policy/for-in-statement-type-checker-policy.h"
#include "policies/while-statement-type-checker-policy/while-statement-type-checker-policy.h"
#include "policies/control-flow-block-type-checker-policy/control-flow-block-type-checker-policy.h"
#include "policies/control-flow-condition-type-checker-policy/control-flow-condition-type-checker-policy.h"
#include "policies/class-property-assignment-statement-type-checker-policy/class-property-assignment-statement-type-checker-policy.h"
#include "policies/expression-statement-type-checker-policy/expression-statement-type-checker-policy.h"
#include "policies/expressions/array-access-expression-type-checker-policy/array-access-expression-type-checker-policy.h"
#include "policies/expressions/array-access-invocation-expression-type-checker-policy/array-access-invocation-expression-type-checker-policy.h"
#include "policies/expressions/array-expression-type-checker-policy/array-expression-type-checker-policy.h"
#include "policies/expressions/binary-expression-type-checker-policy/binary-expression-type-checker-policy.h"
#include "policies/expressions/class-method-invocation-expression-type-checker-policy/class-method-invocation-expression-type-checker-policy.h"
#include "policies/expressions/class-property-access-expression-type-checker-policy/class-property-access-expression-type-checker-policy.h"
#include "policies/expressions/curry-expression-type-checker-policy/curry-expression-type-checker-policy.h"
#include "policies/expressions/function-invocation-expression-type-checker-policy/function-invocation-expression-type-checker-policy.h"
#include "policies/expressions/identifier-expression-type-checker-policy/identifier-expression-type-checker-policy.h"
#include "policies/expressions/lambda-expression-type-checker-policy/lambda-expression-type-checker-policy.h"
#include "policies/expressions/logical-expression-type-checker-policy/logical-expression-type-checker-policy.h"
#include "policies/expressions/new-class-instance-expression-type-checker-policy/new-class-instance-expression-type-checker-policy.h"
#include "policies/expressions/object-access-expression-type-checker-policy/object-access-expression-type-checker-policy.h"
#include "policies/expressions/struct-expression-type-checker-policy/struct-expression-type-checker-policy.h"
#include "policies/expressions/this-expression-type-checker-policy/this-expression-type-checker-policy.h"
#include "policies/expressions/tuple-access-expression-type-checker-policy/tuple-access-expression-type-checker-policy.h"
#include "policies/expressions/tuple-expression-type-checker-policy/tuple-expression-type-checker-policy.h"
#include "policies/expressions/unary-expression-type-checker-policy/unary-expression-type-checker-policy.h"
#include "policies/import-single-module-type-checker-policy/import-single-module-type-checker-policy.h"
#include "policies/module-declaration-type-checker-policy/module-declaration-type-checker-policy.h"
#include "policies/expressions/dref-expression-type-checker-policy/dref-expression-type-checker-policy.h"
#include "policies/array-access-assignment-statement-type-checker-policy/array-access-assignment-statement-type-checker-policy.h"
#include "policies/expressions/concat-expression-type-checker-policy/concat-expression-type-checker-policy.h"
#include "policies/expressions/object-access-invocation-expression-type-checker-policy/object-access-invocation-expression-type-checker-policy.h"
#include "policies/expressions/tuple-access-invocation-expression-type-checker-policy/tuple-access-invocation-expression-type-checker-policy.h"
#include "policies/interface-type-checker-policy/interface-type-checker-policy.h"
#include "policies/custom-type-declaration-type-checker-policy/custom-type-declaration-type-checker-policy.h"
#include "policies/object-access-assignment-statement-type-checker-policy/object-access-assignment-statement-type-checker-policy.h"
#include "policies/tuple-access-assignment-statement-type-checker-policy/tuple-access-assignment-statement-type-checker-policy.h"
#include "policies/module-access-assignment-statement-type-checker-policy/module-access-assignment-statement-type-checker-policy.h"
#include "policies/argument-list-type-checker-policy/argument-list-type-checker-policy.h"
#include "policies/shared-value-assignment-statement-type-checker-policy/shared-value-assignment-statement-type-checker-policy.h"
#include "policies/class-property-shared-value-assignment-statement-type-checker-policy/class-property-shared-value-assignment-statement-type-checker-policy.h"
#include "policies/expressions/module-access-expression-type-checker-policy/module-access-expression-type-checker-policy.h"
#include "policies/array-access-shared-value-assignment-statement-type-checker-policy/array-access-shared-value-assignment-statement-type-checker-policy.h"
#include "policies/object-access-shared-value-assignment-statement-type-checker-policy/object-access-shared-value-assignment-statement-type-checker-policy.h"
#include "policies/tuple-access-shared-value-assignment-statement-type-checker-policy/tuple-access-shared-value-assignment-statement-type-checker-policy.h"
#include "policies/module-access-shared-value-assignment-statement-type-checker-policy/module-access-shared-value-assignment-statement-type-checker-policy.h"
#include "policies/expressions/share-expression-type-checker-policy/share-expression-type-checker-policy.h"

namespace TypeChecker {
    void applyPolicyTo(std::shared_ptr<ASTNode> node, TypeCheckerResult* typeCheckerResult) {
        switch (node->getNodeType()) {
            case AST_VARIABLE_DECLARATION_NODE:
                VariableDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTVariableDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_PROCEDURE_DECLARATION_NODE:
                ProcedureDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_ARGUMENT_LIST_NODE:
                ArgumentListTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_PARAMETER_LIST_NODE:
                ParameterListTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionParameterListNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_PARAMETER_NODE:
                ParameterTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionParameterNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_DECLARATION_NODE:
                FunctionDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_BLOCK_NODE:
                FunctionBlockTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionBlockNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_RETURN_EXPRESSION_NODE:
                FunctionReturnExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(node), typeCheckerResult);
                break;
            case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
                VariableAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTVariableAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
                SharedValueAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTSharedValueAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                ArrayAccessAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTArrayAccessAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
                ArrayAccessSharedValueAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTArrayAccessSharedValueAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                ObjectAccessAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTObjectAccessAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
                ObjectAccessSharedValueAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTObjectAccessSharedValueAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                TupleAccessAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTTupleAccessAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
                TupleAccessSharedValueAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTTupleAccessSharedValueAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                ModuleAccessAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTModuleAccessAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
                ModuleAccessSharedValueAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTModuleAccessSharedValueAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_ENUM_DECLARATION_NODE:
                EnumDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTEnumDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_CLASS_DECLARATION_NODE:
                ClassDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTClassDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_INTERFACE_TYPE_DECLARATION_NODE:
                InterfaceTypeDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTInterfaceTypeDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_CUSTOM_TYPE_DECLARATION_NODE:
                CustomTypeDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_IF_STATEMENT_NODE:
                IfStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTIfStatementNode>(node), typeCheckerResult);
                break;
            case AST_TRY_STATEMENT_NODE:
                TryStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTTryStatementNode>(node), typeCheckerResult);
                break;
            case AST_FOR_IN_STATEMENT_NODE:
                ForInStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTForInStatementNode>(node), typeCheckerResult);
                break;
            case AST_WHILE_STATEMENT_NODE:
                WhileStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTWhileStatementNode>(node), typeCheckerResult);
                break;
            case AST_CONTROL_FLOW_BLOCK_NODE:
                ControlFlowBlockTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTControlFlowBlockNode>(node), typeCheckerResult);
                break;
            case AST_CONTROL_FLOW_CONDITION_NODE:
                ControlFlowConditionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTControlFlowConditionNode>(node), typeCheckerResult);
                break;
            case AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE:
                ClassPropertyAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTClassPropertyAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
                ClassPropertySharedValueAssignmentStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTClassPropertySharedValueAssignmentStatementNode>(node), typeCheckerResult);
                break;
            case AST_EXPRESSION_STATEMENT_NODE:
                ExpressionStatementTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTExpressionStatementNode>(node), typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_EXPRESSION_NODE:
                ArrayAccessExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(node), typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE:
                ArrayAccessInvocationExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTArrayAccessInvocationExpressionNode>(node), typeCheckerResult);
                break;
            case AST_ARRAY_EXPRESSION_NODE:
                ArrayExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTArrayExpressionNode>(node), typeCheckerResult);
                break;
            case AST_BINARY_ARITHMETIC_EXPRESSION_NODE:
                BinaryExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTBinaryArithmeticExpressionNode>(node), typeCheckerResult);
                break;
            case AST_BINARY_COMPARATOR_EXPRESSION_NODE:
                BinaryExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTBinaryComparatorExpressionNode>(node), typeCheckerResult);
                break;
            case AST_CONCAT_EXPRESSION_NODE:
                ConcatExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTConcatExpressionNode>(node), typeCheckerResult);
                break;
            case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
                ClassMethodInvocationExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTClassMethodInvocationExpressionNode>(node), typeCheckerResult);
                break;
            case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
                ClassPropertyAccessExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTClassPropertyAccessExpressionNode>(node), typeCheckerResult);
                break;
            case AST_CURRY_EXPRESSION_NODE:
                CurryExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTCurryExpressionNode>(node), typeCheckerResult);
                break;
            case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
                FunctionInvocationExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTFunctionInvocationExpressionNode>(node), typeCheckerResult);
                break;
            case AST_IDENTIFIER_EXPRESSION_NODE:
                IdentifierExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(node), typeCheckerResult);
                break;
            case AST_LAMBDA_EXPRESSION_NODE:
                LambdaExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTLambdaExpressionNode>(node), typeCheckerResult);
                break;
            case AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE:
                LambdaExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTLambdaWithFatArrowExpressionNode>(node), typeCheckerResult);
                break;
            case AST_LOGICAL_EXPRESSION_NODE:
                LogicalExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTLogicalExpressionNode>(node), typeCheckerResult);
                break;
            case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
                NewClassInstanceExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTNewClassInstanceExpressionNode>(node), typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_EXPRESSION_NODE:
                ObjectAccessExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(node), typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE:
                ObjectAccessInvocationExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTObjectAccessInvocationExpressionNode>(node), typeCheckerResult);
                break;
            case AST_STRUCT_EXPRESSION_NODE:
                StructExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTStructExpressionNode>(node), typeCheckerResult);
                break;
            case AST_THIS_EXPRESSION_NODE:
                ThisExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTThisExpressionNode>(node), typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_EXPRESSION_NODE:
                TupleAccessExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(node), typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE:
                TupleAccessInvocationExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTTupleAccessInvocationExpressionNode>(node), typeCheckerResult);
                break;
            case AST_TUPLE_EXPRESSION_NODE:
                TupleExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTTupleExpressionNode>(node), typeCheckerResult);
                break;
            case AST_UNARY_EXPRESSION_NODE:
                UnaryExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTUnaryExpressionNode>(node), typeCheckerResult);
                break;
            case AST_SHARE_EXPRESSION_NODE:
                ShareExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTShareExpressionNode>(node), typeCheckerResult);
                break;
            case AST_DREF_EXPRESSION_NODE:
                DrefExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTDrefExpressionNode>(node), typeCheckerResult);
                break;
            case AST_MODULE_ACCESS_EXPRESSION_NODE:
                ModuleAccessExpressionTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(node), typeCheckerResult);
                break;
            case AST_LITERAL_EXPRESSION_NODE:
                break;
            case AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE:
                ImportSingleModuleTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTImportSingleModuleDeclarationNode>(node), typeCheckerResult);
                break;
            case AST_MODULE_DECLARATION_NODE:
                ModuleDeclarationTypeCheckerPolicy::apply(std::dynamic_pointer_cast<ASTModuleDeclarationNode>(node), typeCheckerResult);
                break;
            default:
                throw std::logic_error("no type-checker policy found for " + node->toString());
        }
    }
}

