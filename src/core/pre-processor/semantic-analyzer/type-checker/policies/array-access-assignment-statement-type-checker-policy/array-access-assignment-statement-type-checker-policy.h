//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"

namespace ArrayAccessAssignmentStatementTypeCheckerPolicy {
    void apply(ASTArrayAccessAssignmentStatementNode* arrayAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
