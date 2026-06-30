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
#include "policies/expressions/ref-expression-type-checker-policy/ref-expression-type-checker-policy.h"
#include "policies/expressions/dref-expression-type-checker-policy/dref-expression-type-checker-policy.h"
#include "policies/array-access-assignment-statement-type-checker-policy/array-access-assignment-statement-type-checker-policy.h"
#include "policies/expressions/concat-expression-type-checker-policy/concat-expression-type-checker-policy.h"
#include "policies/expressions/object-access-invocation-expression-type-checker-policy/object-access-invocation-expression-type-checker-policy.h"
#include "policies/expressions/tuple-access-invocation-expression-type-checker-policy/tuple-access-invocation-expression-type-checker-policy.h"
#include "policies/interface-type-checker-policy/interface-type-checker-policy.h"
#include "policies/custom-type-declaration-type-checker-policy/custom-type-declaration-type-checker-policy.h"
#include "policies/print-statement-type-checker-policy/print-statement-type-checker-policy.h"
#include "policies/object-access-assignment-statement-type-checker-policy/object-access-assignment-statement-type-checker-policy.h"
#include "policies/tuple-access-assignment-statement-type-checker-policy/tuple-access-assignment-statement-type-checker-policy.h"
#include "policies/module-access-assignment-statement-type-checker-policy/module-access-assignment-statement-type-checker-policy.h"
#include "policies/argument-list-type-checker-policy/argument-list-type-checker-policy.h"
#include "policies/ref-value-assignment-statement-type-checker-policy/ref-value-assignment-statement-type-checker-policy.h"
#include "policies/class-property-ref-value-assignment-statement-type-checker-policy/class-property-ref-value-assignment-statement-type-checker-policy.h"
#include "policies/expressions/module-access-expression-type-checker-policy/module-access-expression-type-checker-policy.h"
#include "policies/array-access-ref-assignment-statement-type-checker-policy/array-access-ref-assignment-statement-type-checker-policy.h"
#include "policies/object-access-ref-assignment-statement-type-checker-policy/object-access-ref-assignment-statement-type-checker-policy.h"
#include "policies/tuple-access-ref-assignment-statement-type-checker-policy/tuple-access-ref-assignment-statement-type-checker-policy.h"
#include "policies/module-access-ref-assignment-statement-type-checker-policy/module-access-ref-assignment-statement-type-checker-policy.h"

namespace TypeChecker {
    void applyPolicyTo(ASTNode* node, TypeCheckerResult* typeCheckerResult) {
        switch (node->getNodeType()) {
            case AST_VARIABLE_DECLARATION_NODE:
                VariableDeclarationTypeCheckerPolicy::apply((ASTVariableDeclarationNode*) node, typeCheckerResult);
                break;
            case AST_PROCEDURE_DECLARATION_NODE:
                ProcedureDeclarationTypeCheckerPolicy::apply((ASTProcedureDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_ARGUMENT_LIST_NODE:
                ArgumentListTypeCheckerPolicy::apply((ASTFunctionArgumentListNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_PARAMETER_LIST_NODE:
                ParameterListTypeCheckerPolicy::apply((ASTFunctionParameterListNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_PARAMETER_NODE:
                ParameterTypeCheckerPolicy::apply((ASTFunctionParameterNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_DECLARATION_NODE:
                FunctionDeclarationTypeCheckerPolicy::apply((ASTFunctionDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_BLOCK_NODE:
                FunctionBlockTypeCheckerPolicy::apply((ASTFunctionBlockNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_RETURN_EXPRESSION_NODE:
                FunctionReturnExpressionTypeCheckerPolicy::apply((ASTFunctionReturnExpressionNode*)node, typeCheckerResult);
                break;
            case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
                VariableAssignmentStatementTypeCheckerPolicy::apply((ASTVariableAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE:
                RefValueAssignmentStatementTypeCheckerPolicy::apply((ASTRefValueAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                ArrayAccessAssignmentStatementTypeCheckerPolicy::apply((ASTArrayAccessAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE:
                ArrayAccessRefAssignmentStatementTypeCheckerPolicy::apply((ASTArrayAccessRefAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                ObjectAccessAssignmentStatementTypeCheckerPolicy::apply((ASTObjectAccessAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE:
                ObjectAccessRefAssignmentStatementTypeCheckerPolicy::apply((ASTObjectAccessRefAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                TupleAccessAssignmentStatementTypeCheckerPolicy::apply((ASTTupleAccessAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE:
                TupleAccessRefAssignmentStatementTypeCheckerPolicy::apply((ASTTupleAccessRefAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
                ModuleAccessAssignmentStatementTypeCheckerPolicy::apply((ASTModuleAccessAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE:
                ModuleAccessRefAssignmentStatementTypeCheckerPolicy::apply((ASTModuleAccessRefAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_ENUM_DECLARATION_NODE:
                EnumDeclarationTypeCheckerPolicy::apply((ASTEnumDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_CLASS_DECLARATION_NODE:
                ClassDeclarationTypeCheckerPolicy::apply((ASTClassDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_INTERFACE_TYPE_DECLARATION_NODE:
                InterfaceTypeDeclarationTypeCheckerPolicy::apply((ASTInterfaceTypeDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_CUSTOM_TYPE_DECLARATION_NODE:
                CustomTypeDeclarationTypeCheckerPolicy::apply((ASTCustomTypeDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_IF_STATEMENT_NODE:
                IfStatementTypeCheckerPolicy::apply((ASTIfStatementNode*)node, typeCheckerResult);
                break;
            case AST_TRY_STATEMENT_NODE:
                TryStatementTypeCheckerPolicy::apply((ASTTryStatementNode*)node, typeCheckerResult);
                break;
            case AST_FOR_IN_STATEMENT_NODE:
                ForInStatementTypeCheckerPolicy::apply((ASTForInStatementNode*)node, typeCheckerResult);
                break;
            case AST_WHILE_STATEMENT_NODE:
                WhileStatementTypeCheckerPolicy::apply((ASTWhileStatementNode*)node, typeCheckerResult);
                break;
            case AST_CONTROL_FLOW_BLOCK_NODE:
                ControlFlowBlockTypeCheckerPolicy::apply((ASTControlFlowBlockNode*)node, typeCheckerResult);
                break;
            case AST_CONTROL_FLOW_CONDITION_NODE:
                ControlFlowConditionTypeCheckerPolicy::apply((ASTControlFlowConditionNode*)node, typeCheckerResult);
                break;
            case AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE:
                ClassPropertyAssignmentStatementTypeCheckerPolicy::apply((ASTClassPropertyAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE:
                ClassPropertyRefValueAssignmentStatementTypeCheckerPolicy::apply((ASTClassPropertyRefValueAssignmentStatementNode*)node, typeCheckerResult);
                break;
            case AST_EXPRESSION_STATEMENT_NODE:
                ExpressionStatementTypeCheckerPolicy::apply((ASTExpressionStatementNode*)node, typeCheckerResult);
                break;
            case AST_PRINT_STATEMENT_NODE:
                PrintStatementTypeCheckerPolicy::apply((ASTPrintStatementNode*)node, typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_EXPRESSION_NODE:
                ArrayAccessExpressionTypeCheckerPolicy::apply((ASTArrayAccessExpressionNode*)node, typeCheckerResult);
                break;
            case AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE:
                ArrayAccessInvocationExpressionTypeCheckerPolicy::apply((ASTArrayAccessInvocationExpressionNode*)node, typeCheckerResult);
                break;
            case AST_ARRAY_EXPRESSION_NODE:
                ArrayExpressionTypeCheckerPolicy::apply((ASTArrayExpressionNode*)node, typeCheckerResult);
                break;
            case AST_BINARY_ARITHMETIC_EXPRESSION_NODE:
                BinaryExpressionTypeCheckerPolicy::apply((ASTBinaryArithmeticExpressionNode*)node, typeCheckerResult);
                break;
            case AST_BINARY_COMPARATOR_EXPRESSION_NODE:
                BinaryExpressionTypeCheckerPolicy::apply((ASTBinaryComparatorExpressionNode*)node, typeCheckerResult);
                break;
            case AST_CONCAT_EXPRESSION_NODE:
                ConcatExpressionTypeCheckerPolicy::apply((ASTConcatExpressionNode*)node, typeCheckerResult);
                break;
            case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
                ClassMethodInvocationExpressionTypeCheckerPolicy::apply((ASTClassMethodInvocationExpressionNode*)node, typeCheckerResult);
                break;
            case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
                ClassPropertyAccessExpressionTypeCheckerPolicy::apply((ASTClassPropertyAccessExpressionNode*)node, typeCheckerResult);
                break;
            case AST_CURRY_EXPRESSION_NODE:
                CurryExpressionTypeCheckerPolicy::apply((ASTCurryExpressionNode*)node, typeCheckerResult);
                break;
            case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
                FunctionInvocationExpressionTypeCheckerPolicy::apply((ASTFunctionInvocationExpressionNode*)node, typeCheckerResult);
                break;
            case AST_IDENTIFIER_EXPRESSION_NODE:
                IdentifierExpressionTypeCheckerPolicy::apply((ASTIdentifierExpressionNode*)node, typeCheckerResult);
                break;
            case AST_LAMBDA_EXPRESSION_NODE:
                LambdaExpressionTypeCheckerPolicy::apply((ASTLambdaExpressionNode*)node, typeCheckerResult);
                break;
            case AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE:
                LambdaExpressionTypeCheckerPolicy::apply((ASTLambdaWithFatArrowExpressionNode*)node, typeCheckerResult);
                break;
            case AST_LOGICAL_EXPRESSION_NODE:
                LogicalExpressionTypeCheckerPolicy::apply((ASTLogicalExpressionNode*)node, typeCheckerResult);
                break;
            case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
                NewClassInstanceExpressionTypeCheckerPolicy::apply((ASTNewClassInstanceExpressionNode*)node, typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_EXPRESSION_NODE:
                ObjectAccessExpressionTypeCheckerPolicy::apply((ASTObjectAccessExpressionNode*)node, typeCheckerResult);
                break;
            case AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE:
                ObjectAccessInvocationExpressionTypeCheckerPolicy::apply((ASTObjectAccessInvocationExpressionNode*)node, typeCheckerResult);
                break;
            case AST_STRUCT_EXPRESSION_NODE:
                StructExpressionTypeCheckerPolicy::apply((ASTStructExpressionNode*)node, typeCheckerResult);
                break;
            case AST_THIS_EXPRESSION_NODE:
                ThisExpressionTypeCheckerPolicy::apply((ASTThisExpressionNode*)node, typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_EXPRESSION_NODE:
                TupleAccessExpressionTypeCheckerPolicy::apply((ASTTupleAccessExpressionNode*)node, typeCheckerResult);
                break;
            case AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE:
                TupleAccessInvocationExpressionTypeCheckerPolicy::apply((ASTTupleAccessInvocationExpressionNode*)node, typeCheckerResult);
                break;
            case AST_TUPLE_EXPRESSION_NODE:
                TupleExpressionTypeCheckerPolicy::apply((ASTTupleExpressionNode*)node, typeCheckerResult);
                break;
            case AST_UNARY_EXPRESSION_NODE:
                UnaryExpressionTypeCheckerPolicy::apply((ASTUnaryExpressionNode*)node, typeCheckerResult);
                break;
            case AST_REF_EXPRESSION_NODE:
                RefExpressionTypeCheckerPolicy::apply((ASTRefExpressionNode*)node, typeCheckerResult);
                break;
            case AST_DREF_EXPRESSION_NODE:
                DrefExpressionTypeCheckerPolicy::apply((ASTDrefExpressionNode*)node, typeCheckerResult);
                break;
            case AST_MODULE_ACCESS_EXPRESSION_NODE:
                ModuleAccessExpressionTypeCheckerPolicy::apply((ASTModuleAccessExpressionNode*)node, typeCheckerResult);
                break;
            case AST_LITERAL_EXPRESSION_NODE:
                break;
            case AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE:
                ImportSingleModuleTypeCheckerPolicy::apply((ASTImportSingleModuleDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_MODULE_DECLARATION_NODE:
                ModuleDeclarationTypeCheckerPolicy::apply((ASTModuleDeclarationNode*)node, typeCheckerResult);
                break;
            default:
                throw std::logic_error("no type-checker policy found for " + node->toString());
        }
    }
}

