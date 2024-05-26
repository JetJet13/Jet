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

namespace TypeChecker {
    void applyPolicyTo(ASTNode* node, TypeCheckerResult* typeCheckerResult) {
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
            default:
                throw std::logic_error("no type-signature policy found for " + node->toString());
        }
    }
}

