//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"

namespace VariableAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTVariableAssignmentStatementNode> variableAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
