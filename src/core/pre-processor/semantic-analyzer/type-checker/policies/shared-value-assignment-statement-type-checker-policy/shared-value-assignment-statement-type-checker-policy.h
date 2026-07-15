//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-shared-value-assignment-statement-node.h"

namespace SharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTSharedValueAssignmentStatementNode> sharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
