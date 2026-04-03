//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-assignment-statement-node.h"

namespace ModuleAccessAssignmentStatementTypeCheckerPolicy {
    void apply(ASTModuleAccessAssignmentStatementNode* moduleAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_MODULE_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
