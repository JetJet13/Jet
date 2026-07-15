//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-shared-value-assignment-statement-node.h"

namespace ModuleAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> moduleAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
