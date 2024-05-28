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
#include "policies/for-statement-type-checker-policy/for-statement-type-checker-policy.h"
#include "policies/while-statement-type-checker-policy/while-statement-type-checker-policy.h"
#include "policies/control-flow-block-type-checker-policy/control-flow-block-type-checker-policy.h"
#include "policies/control-flow-condition-type-checker-policy/control-flow-condition-type-checker-policy.h"
#include "policies/class-property-assignment-statement-type-checker-policy/class-property-assignment-statement-type-checker-policy.h"

namespace TypeChecker {
    void applyPolicyTo(ASTNode* node, TypeCheckerResult* typeCheckerResult) {
// todo: add type checker policy for: expression statement
        switch (node->getNodeType()) {
            case AST_VARIABLE_DECLARATION_NODE:
                VariableDeclarationTypeCheckerPolicy::apply((ASTVariableDeclarationNode*) node, typeCheckerResult);
                break;
            case AST_PROCEDURE_DECLARATION_NODE:
                ProcedureDeclarationTypeCheckerPolicy::apply((ASTProcedureDeclarationNode*)node, typeCheckerResult);
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
            case AST_ENUM_DECLARATION_NODE:
                EnumDeclarationTypeCheckerPolicy::apply((ASTEnumDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_CLASS_DECLARATION_NODE:
                ClassDeclarationTypeCheckerPolicy::apply((ASTClassDeclarationNode*)node, typeCheckerResult);
                break;
            case AST_IF_STATEMENT_NODE:
                IfStatementTypeCheckerPolicy::apply((ASTIfStatementNode*)node, typeCheckerResult);
                break;
            case AST_TRY_STATEMENT_NODE:
                TryStatementTypeCheckerPolicy::apply((ASTTryStatementNode*)node, typeCheckerResult);
                break;
            case AST_FOR_STATEMENT_NODE:
                ForStatementTypeCheckerPolicy::apply((ASTForStatementNode*)node, typeCheckerResult);
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
            default:
                throw std::logic_error("no type-signature policy found for " + node->toString());
        }
    }
}

