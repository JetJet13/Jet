//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-object-access-shared-value-assignment-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ObjectAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> objectAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
}

#endif //JETLANG_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_TYPE_CHECKER_POLICY_H
