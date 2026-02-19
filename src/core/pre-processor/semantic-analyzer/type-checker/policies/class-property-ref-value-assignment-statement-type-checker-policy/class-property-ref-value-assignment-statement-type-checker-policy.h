//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-ref-value-assignment-statement-node.h"

namespace ClassPropertyRefValueAssignmentStatementTypeCheckerPolicy {
    void apply(ASTClassPropertyRefValueAssignmentStatementNode* classPropertyRefValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
