//
// Created by Johny Georges on 2024-05-21.
//

#include "type-checker.h"
#include "policies/procedure-declaration-type-checker-policy/procedure-declaration-type-checker-policy.h"
#include "policies/variable-declaration-type-checker-policy/variable-declaration-type-checker-policy.h"
#include "policies/parameter-list-type-checker-policy/parameter-list-type-checker-policy.h"
#include "policies/parameter-type-checker-policy/parameter-type-checker-policy.h"


TypeCheckerResult TypeChecker::applyPolicyTo(ASTNode* node, TypeCheckerRuleList* rules) {
    switch (node->getNodeType()) {
        case AST_VARIABLE_DECLARATION_NODE:
            return VariableDeclarationTypeCheckerPolicy::apply((ASTVariableDeclarationNode*) node, rules);
        case AST_PROCEDURE_DECLARATION_NODE:
            return ProcedureDeclarationTypeCheckerPolicy::apply((ASTProcedureDeclarationNode*)node, rules);
        case AST_FUNCTION_PARAMETER_LIST_NODE:
            return ParameterListTypeCheckerPolicy::apply((ASTFunctionParameterListNode*)node, rules);
        case AST_FUNCTION_PARAMETER_NODE:
            return ParameterTypeCheckerPolicy::apply((ASTFunctionParameterNode*)node, rules);
        default:
            throw std::logic_error("no type-signature policy found for " + node->toString());
    }
}