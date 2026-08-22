//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-shared-value-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ClassPropertySharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> classPropertySharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
