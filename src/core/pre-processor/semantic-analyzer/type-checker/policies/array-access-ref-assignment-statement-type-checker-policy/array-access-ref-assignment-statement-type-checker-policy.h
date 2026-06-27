//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-array-access-ref-assignment-statement-node.h"

namespace ArrayAccessRefAssignmentStatementTypeCheckerPolicy {
    void apply(ASTArrayAccessRefAssignmentStatementNode* arrayAccessRefAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
}

#endif //JETLANG_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
